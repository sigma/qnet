/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _OSDSPLASH_H_
#define _OSDSPLASH_H_

#include "page.h"

class OsdSplash : public Page {
    Q_OBJECT

public:
    OsdSplash(QWidget *parent, const char *name, Master * session);
    ~OsdSplash();

    bool isSlave() {return false;}

public slots:
    void append(const QString & msg);
};

#endif
