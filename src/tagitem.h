/*
 *  File: tagitem.h
 *  Created: Thursday, April 8, 2004
 *  Time-stamp: <08/04/2004 22:05:17 Yann Hodique>
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

#ifndef _TAGITEM_H_
#define _TAGITEM_H_

class TagItem {
public:
    TagItem(QString n="", QString f="", QString s="", int c=0,
	    bool t=false, bool u=false, bool e=false, int l=3) {
	name=n;
	family = f;
	style = s;
	color = c;
	strike = t;
	underline = u;
	collapse = e;
	size = l;
    }
    QString name;
    QString family;
    QString style;
    int color;
    bool strike;
    bool underline;
    bool collapse;
    int size;
};


#endif /* _TAGITEM_H_ */
