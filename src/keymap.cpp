/*
 *  File: keymap.cpp
 *  Created: Thursday, December 30, 2004
 *  Time-stamp: <31/12/2004 18:11:47 Yann Hodique>
 *  Copyright: Yann Hodique
 *  Email: Yann.Hodique@lifl.fr
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

KeyMap KeyMap::global_keymap;

KeyMap::KeyMap(QObject *parent) : QObject(parent) {}

KeyMap::~KeyMap() {}

void KeyMap::setKey(const QKeySequence& key, SCM scm) {
    keys.insert(key,scm);
}

void KeyMap::unsetKey(const QKeySequence& key) {
    keys.remove(key);
}
