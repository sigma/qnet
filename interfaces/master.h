/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _MASTER_H_
#define _MASTER_H_

#include <qwidget.h>
#include <qstring.h>

class Master : public QWidget {
    Q_OBJECT
public:  
    Master(QWidget* parent = 0, const char* name = 0, WFlags fl = 0) : QWidget(parent, name, fl) {}
    virtual ~Master() {}
    
    virtual void send(QString &) = 0;
    
public slots:
    virtual void slotLinkClicked(const QString &) {}
};

#endif
