/*
 *  File: SessionItem.h
 *  Created: Saturday, April 10, 2004
 *  Time-stamp: <10/04/2004 09:31:17 Yann Hodique>
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

#ifndef _SESSIONITEM_H_
#define _SESSIONITEM_H_

class SessionItem {
public:
    SessionItem(QString n="", QString h="", QString p="", QString l="", QString x="", bool b=false) {
        name = n;
        host = h;
        port = p;
        login = l;
        password = x;
        autoconnect = b;
    }
    QString name;
    QString host;
    QString port;
    QString login;
    QString password;
    bool autoconnect;
};


#endif /* _SESSIONITEM_H_ */
