/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _SESSIONSDIALOG_H_
#define _SESSIONSDIALOG_H_

#include "sessionsdialogbase.h"

#include <qwidget.h>
#include <qstring.h>
#include <qmap.h>

/**
 * 
 * Yann Hodique
 **/
class SessionsDialog : public SessionsDialogBase {
    Q_OBJECT

public:

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

    SessionsDialog(QWidget *parent = 0, const char *name = 0);
    ~SessionsDialog();

    QMap<QString,SessionItem> map;

public slots:
    void addSessionItem(SessionItem &, int index = -1);
    void delSessionItem(const QString&);
    void slotSubs();
    void slotAdd();
    void slotDel();
    void slotDown();
    void slotUp();
    void slotUpdateInfo(const QString &);

};

#endif
