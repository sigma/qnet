/*  Time-stamp: <08/02/2005 09:22:18 Yann Hodique>  */

/**
 *  @file keymap.h
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
    static KeyMap* getCurrentKeyMap() {return current_keymap;}

    void setKey(const QKeySequence&, SCM);
    void setKey(const QKeySequence&, KeyMap*);

    void unsetKey(const QKeySequence&);

    typedef enum {
        Accepted,
        Keymap,
        Rejected
    } ExecutionStatus;

    ExecutionStatus execute(const QKeySequence&) const;

private:
    static KeyMap global_keymap;
    static KeyMap * current_keymap;
    QMap<QKeySequence,SCM> keys;
    QMap<QKeySequence,KeyMap*> maps;
};	// end of class KeyMap


#endif /* _KEYMAP_H_ */
