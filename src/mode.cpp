/*  Time-stamp: <07/02/2005 21:22:35 Yann Hodique>  */

/**
 *  @file mode.cpp
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

#include "mode.h"
#include "fontlock.h"
#include "keymap.h"

Mode::Mode(const QString &n) : name(n) {
    parent = 0;
    font_lock = new FontLock;
    key_map = new KeyMap;
}

Mode::~Mode() {
    if(font_lock)
        delete font_lock;
    if(key_map)
        delete key_map;
}

void Mode::derive(Mode * p) {
    if(parent) {
        qDebug("Mode::derive() : mode already has a parent");
        return;
    }
    parent = p;
    p->children << this;

}

QMap<QString,Mode*> Mode::existing_modes;

Mode* Mode::getMode(const QString& name) {
    QMap<QString,Mode*>::Iterator it = existing_modes.find(name);
    if(it != existing_modes.end())
        return *it;
    else {
        Mode * m = new Mode(name);
        existing_modes.insert(name,m);
        return m;
    }
}

Mode* Mode::getMode(QWidget* w) {
    if(!w) return 0;
    return getMode(w->metaObject()->className());
}
