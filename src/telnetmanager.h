/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _TELNETMANAGER_H_
#define _TELNETMANAGER_H_

#include <qobject.h>

class QSocket;
class QString;
class ChatSession;
class QChar;

/**
 * 
 * Yann Hodique
 **/
class TelnetManager : public QObject {
    Q_OBJECT

public:
    TelnetManager(QWidget *parent=0, const char *name=0);
    ~TelnetManager();

    void setArgs(QString, QString);
    void start();
    void setLogin(QString login);
    void setPassword(QString password);

public slots:
    void readStdout();
    void writeStdin(QString);
    void slotProcessExited();
    void slotError(int);
    
private:
    QSocket * socket;
    ChatSession * mtp;
    QString suspended;
    QString host;
    int port;

    QChar IAC;
    QString login;
    QString password;

signals:
    void processExited();
};

#endif
