/***************************************************************************
 *   Copyright (C) 2003 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _CRON_H_
#define _CRON_H_

#include "page.h"

class QTimer;

class Cron : public Page {
    Q_OBJECT

public:
    Cron(QWidget *parent, const char *name, Master * session);
    ~Cron();

    bool isSlave() {return false;}

public slots:
    void timeout();
    void append(const QString & msg);
    void stop();

private:
    QTimer *m_timer;
    int time;
    QString m_action;
    bool received;
};

#endif
