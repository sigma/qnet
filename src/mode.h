/*  Time-stamp: <07/02/2005 20:18:01 Yann Hodique>  */

/**
 *  @file mode.h
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

#ifndef _MODE_H_
#define _MODE_H_

#include <QString>
#include <QList>
#include <QMap>
#include <QWidget>

class FontLock;
class KeyMap;

class Mode {

public:
    static Mode* getMode(const QString&);
    static Mode* getMode(QWidget*);

    FontLock* getFontLock() const {return font_lock;}
    KeyMap* getKeyMap() const {return key_map;}
    void derive(Mode *);

private:
    Mode(const QString &);
    ~Mode();

    QString name;
    FontLock *font_lock;
    KeyMap *key_map;
    Mode *parent;
    QList<Mode*> children;

    static QMap<QString,Mode*> existing_modes;
};	// end of class Mode


#endif /* _MODE_H_ */
