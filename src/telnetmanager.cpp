/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include <iostream>

#include <qsocket.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qregexp.h>

#include "ChatSession.h"
#include "telnetmanager.h"

using namespace std;

TelnetManager::TelnetManager(QWidget *parent, const char *name)
        : QObject(parent, name) {
    mtp = (ChatSession *)parent;
    socket = new QSocket(this);

    IAC = QChar(char(255));

    connect(socket, SIGNAL(readyRead()),
            this, SLOT(readStdout()));
    connect(socket, SIGNAL(connectionClosed()),
            this, SLOT(slotProcessExited()));
    connect(socket, SIGNAL(error(int)),
            this, SLOT(slotError(int)));
}


TelnetManager::~TelnetManager() {
    socket->close();
    delete socket;
}

void TelnetManager::setArgs(const QString& host, const QString& port) {
    this->host = host;
    this->port = port.toInt();
}

void TelnetManager::start() {
    socket->connectToHost(host,port);
}

void TelnetManager::readStdout() {
    int available = socket->bytesAvailable();

    char * buffer = new char[available+1];
    socket->readBlock(buffer,available);
    buffer[available] = 0;

    QString text(buffer);
    delete[] buffer;

    // IAC management
    text = text.replace(QRegExp(QString("^") + IAC + QString("..")),"").replace(QRegExp(QString(IAC) + IAC),QString(IAC));

    // "\r\n" management
    text = text.replace(QRegExp(QString("\r\n")),"\n");

    //Login and Password management (no "\n")
    if (text.endsWith("Login: ")) {
        text += "\n";
        if (login != "")
            writeStdin(login);
        login = "";
    }

    if (text.endsWith("Password: ")) {
        text += "\n";
        if (password != "")
            writeStdin(password);
        password = "";
    }

    text = suspended + text;
    QStringList list = QStringList::split("\n",text);
    QStringList::Iterator end_it;

    if (!text.endsWith("\n")) {
        end_it = list.end();
        end_it--;
        suspended = *end_it;
    } else {
        suspended = "";
        end_it = list.end();
    }
    for (QStringList::Iterator it = list.begin(); it != end_it; ++it) {
        mtp->displayStdout(*it);
    }
}

void TelnetManager::writeStdin(const QString& msg) {
    QString to_write(msg);
    to_write = to_write.replace(QRegExp("\n"),"\r\n") + "\r\n";
    
    int index = 0;
    while ((index = to_write.find(IAC,index)) != -1) {
        to_write.insert(index,IAC);
        index += 2;
    }

    socket->writeBlock(to_write.latin1(),to_write.length());
}

void TelnetManager::slotProcessExited() {
    emit processExited();
}

void TelnetManager::setLogin(const QString& login) {
    this->login = login;
}

void TelnetManager::setPassword(const QString& password) {
    this->password = password;
}

void TelnetManager::slotError(int error_code) {
    switch (error_code) {
	case QSocket::ErrConnectionRefused:
	    cerr << "QSocket::ErrConnectionRefused" << endl;
	    break;
	case QSocket::ErrHostNotFound:
	    cerr << "QSocket::ErrHostNotFound" << endl;
	    break;
	case QSocket::ErrSocketRead:
	    cerr << "QSocket::ErrSocketRead" << endl;
	    break;
	default:
	    cerr << "Unknown QSocket error" << endl;
	    break;
    }
}
