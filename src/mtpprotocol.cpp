/*  Time-stamp: <09/02/2005 20:53:40 Yann Hodique>  */

/**
 *  @file mtpprotocol.cpp
 *  @date Tuesday, December 28, 2004
 *  @author Yann Hodique <Yann.Hodique@lifl.fr>
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
#include "interactiveiodevice.h"

#include <QIODevice>
#include <QStringList>

MtpProtocol::MtpProtocol(QObject * parent) : QObject(parent) {
    io = 0;

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
    writeIO(str);
}

void MtpProtocol::installIO(QIODevice *s) {
    if(io) uninstallIO();
    io = s;
    connect(s, SIGNAL(readyRead()), this, SLOT(readIO()));

    if(dynamic_cast<InteractiveIODevice*>(s)) {
        connect(this, SIGNAL(loginQuery()), s, SLOT(sendLogin()));
        connect(this, SIGNAL(passwdQuery()), s, SLOT(sendPasswd()));
    }
}

void MtpProtocol::uninstallIO() {
    if(io) {
        disconnect(io, SIGNAL(readyRead()), this, SLOT(readIO()));

        if(dynamic_cast<InteractiveIODevice*>(io)) {
            disconnect(this, SIGNAL(loginQuery()), io, SLOT(sendLogin()));
            disconnect(this, SIGNAL(passwdQuery()), io, SLOT(sendPasswd()));
        }
        io->deleteLater();
        io = 0;
    }
}

void MtpProtocol::readIO() {
    if(!io) return;

    Q_LONGLONG available = io->bytesAvailable();

    char * buffer = new char[available+1];
    io->read(buffer,available);
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
        emit loginQuery();
    }

    if (text.endsWith("Password: ")) {
        text += "\n";
        emit passwdQuery();
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

void MtpProtocol::writeIO(const QString& s) {
    if(io)
        io->write(s.toAscii());
}
