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

#include "MtpContext.h"

class Master : public QWidget {
    Q_OBJECT
public:  
    Master(QWidget* parent = 0, const char* name = 0, WFlags fl = 0) : QWidget(parent, name, fl) {
	m_context = new MtpContext;
    }
    
    ~Master() {
	delete m_context;
    }
    
    MtpContext* context() { return m_context; }
    
    virtual void displayStderr(QString) = 0;
    virtual void displayStdout(QString) = 0;
    virtual void send(QString &) = 0;
    
public slots:
    virtual void slotLinkClicked(const QString &) {}

private:
MtpContext* m_context;
};

#endif
