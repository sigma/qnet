/*
 *  File: keymap.h
 *  Created: Thursday, December 30, 2004
 *  Time-stamp: <31/12/2004 18:13:36 Yann Hodique>
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

#ifndef _KEYMAP_H_
#define _KEYMAP_H_

#include <QObject>
#include <QKeySequence>
#include <QMap>

#include <libguile.h>

class KeyMap : public QObject {

    Q_OBJECT

public:
    KeyMap(QObject *parent = 0);

    ~KeyMap();

    static const KeyMap& getGlobalKeyMap() {return global_keymap;}

    void setKey(const QKeySequence&, SCM);
    void unsetKey(const QKeySequence&);

private:
    static KeyMap global_keymap;
    QMap<QKeySequence,SCM> keys;
};	// end of class KeyMap


#endif /* _KEYMAP_H_ */
