/*
 *  File: mtpprotocol.cpp
 *  Created: Tuesday, December 28, 2004
 *  Time-stamp: <28/12/2004 15:26:53 Yann Hodique>
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

#include "mtpprotocol.h"

#include <QTcpSocket>
#include <QStringList>

MtpProtocol::MtpProtocol(QObject * parent) : QObject(parent) {
    socket = 0;
    host = QString::null;
    port = 0;
    login = QString::null;
    passwd = QString::null;

    IAC = QChar(char(255));
    cmd_reg = QRegExp(QString("^") + IAC + QString(".."));
}

MtpProtocol::~MtpProtocol() {}

bool MtpProtocol::lineAvailable() const {
    return lines.size() > 0;
}

QString MtpProtocol::readLine() {
    if(lineAvailable())
        return lines.dequeue();
    return QString::null;
}

void MtpProtocol::writeLine(const QString& s) {
    QString str(s);
    str = str.replace("\n","\r\n");
    if(!str.endsWith("\n"))
        str += "\r\n";
    writeSocket(str);
}

void MtpProtocol::connectToHost() {
    if(socket == 0 && host != QString::null && port != 0) {
        socket = new QTcpSocket(this);
        installSocket(socket);
        socket->connectToHost(host,port);
    }
}

void MtpProtocol::reconnectToHost() {
    if(socket) {
        uninstallSocket(socket);
        socket->deleteLater();
    }
    connectToHost();
}

void MtpProtocol::installSocket(QTcpSocket *s) {
    connect(s, SIGNAL(readyRead()), this, SLOT(readSocket()));
}

void MtpProtocol::uninstallSocket(QTcpSocket *s) {
    disconnect(s, SIGNAL(readyRead()), this, SLOT(readSocket()));
}

void MtpProtocol::readSocket() {
    Q_LONGLONG available = socket->bytesAvailable();

    char * buffer = new char[available+1];
    socket->read(buffer,available);
    buffer[available] = 0;

    QString text(buffer);
    delete[] buffer;

    // IAC management
    if(text.startsWith(QString(IAC)) && text.size() > 3) {
        int cmd = text.at(1).ascii() << sizeof(char) + text.at(2).ascii();
        emit cmdSignal(cmd);
        text = text.replace(cmd_reg,"").replace(QString(IAC) + IAC,QString(IAC));
    }
    // "\r\n" management
    text = text.replace("\r\n","\n");

    // beep management
    if (text.startsWith("\a")) {
        text = text.replace("\a","");
        emit beepSignal();
    }

    //Login and Password management (no "\n")
    if (text.endsWith("Login: ")) {
        text += "\n";
        if (login != "")
            writeLine(login);
//        login = "";
    }

    if (text.endsWith("Password: ")) {
        text += "\n";
        if (passwd != "")
            writeLine(passwd);
        else
            emit passwdQuery();
//        passwd = "";
    }

    text = suspended + text;
    QStringList list = text.split('\n',QString::SkipEmptyParts);
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
        lines.enqueue(*it);
    }
    if(list.size())
        emit readyRead();
}

void MtpProtocol::writeSocket(const QString& s) {
    socket->write(s.toAscii());
}
