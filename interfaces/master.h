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

class Master : public QObject {
    Q_OBJECT
        public:
    Master(QObject* parent = 0, const char* name = 0) : QObject(parent, name) {
        m_context = new MtpContext;
    }

    ~Master() {
        delete m_context;
    }

    MtpContext* context() { return m_context; }
    virtual bool isLogged() = 0;
    virtual void displayStderr(const QString&) = 0;
    virtual void displayStdout(const QString&) = 0;
    virtual void send(const QString &) = 0;

public slots:
    virtual void slotLinkClicked(const QString &) {}
    virtual void closeSession() {}
    virtual void slotReconnect() {}

private:
    MtpContext* m_context;

signals:
    void active();
    void inactive();
};

#endif
