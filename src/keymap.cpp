/*  Time-stamp: <09/05/2005 21:52:13 Yann Hodique>  */

/**
 *  @file keymap.cpp
 *  @date Thursday, December 30, 2004
 *  @author Yann Hodique <Yann.Hodique@lifl.fr>
 */

/************************************************************************
 *                                                                      *
 * This program is free software; you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 ************************************************************************/

#include "keymap.h"
#include "scm.h"

KeyMap KeyMap::global_keymap;
KeyMap* KeyMap::current_keymap = &global_keymap;

QString KeyMap::keyFromKeyEvent(QKeyEvent *e) {
    if(!e) return QString::null;
    Qt::KeyboardModifiers mod = e->modifiers();

    switch(e->key()) {
        case Qt::Key_Shift:
        case Qt::Key_Control:
        case Qt::Key_Meta:
        case Qt::Key_Alt:
        case Qt::Key_Super_L:
        case Qt::Key_Super_R:
        case Qt::Key_Hyper_L:
        case Qt::Key_Hyper_R:
            return QString::null;
        default:
            return QString(((mod & Qt::ControlModifier) ? "Ctrl+" : ""))
                + ((mod & Qt::ShiftModifier) ? "Shift+" : "")
                + ((mod & Qt::MetaModifier) ? "Meta+" : "")
                + ((mod & Qt::AltModifier) ? "Alt+" : "")
                + e->key();
    }
}

KeyMap::KeyMap(QObject *parent) : QObject(parent) {}

KeyMap::~KeyMap() {}

void KeyMap::setKey(const QKeySequence& key, SCM scm) {
    maps.remove(key);
    keys.insert(key,scm);
}

void KeyMap::setKey(const QKeySequence& key, KeyMap* map) {
    keys.remove(key);
    maps.insert(key,map);
}

void KeyMap::unsetKey(const QKeySequence& key) {
    keys.remove(key);
}

KeyMap::ExecutionStatus KeyMap::execute(const QKeySequence& key) const {
    QMap<QKeySequence,KeyMap*>::ConstIterator it1;
    QMap<QKeySequence,SCM>::ConstIterator it2;
    if((it1 = maps.find(key)) != maps.end()) {
        current_keymap = *it1;
        return Keymap;
    }
    else if((it2 = keys.find(key)) != keys.end()) {
        Scm::getInstance()->eval(*it2);
        return Accepted;
    }
    else {
        current_keymap = &global_keymap;
        return Rejected;
    }
}
