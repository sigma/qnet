/***************************************************************************
 *   Copyright (C) 2003 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include <qregexp.h>
#include <qtimer.h>

#include "cron.h"

PLUGIN_FACTORY(Cron,"cron");

Cron::Cron(QWidget * /*parent*/, const char *name, Master * session)
    : Page(0, name, session) {
    m_timer = new QTimer(this);

    connect(m_timer, SIGNAL(timeout()),
            SLOT(timeout()));
    connect(session, SIGNAL(inactive()),
            SLOT(stop()));

}

Cron::~Cron() {}

void Cron::timeout() {
    if(!received) {
        m_timer->stop();
        getMaster()->closeSession();
    }
    else {
        received = false;
        getMaster()->send(m_action);
    }
}

void Cron::stop() {
    m_timer->stop();
}

void Cron::append(const QString & msg) {
    if(msg == "restart") {
        received = true;
        return;
    }

    QRegExp re("(start|shot) +(\\d+) +([^ ].*)");
    if(re.exactMatch(msg)) {
        time = re.cap(2).toInt();
        m_action = re.cap(3);
        getMaster()->send(m_action);
        m_timer->start(time,re.cap(1) == "shot");
    }
}
