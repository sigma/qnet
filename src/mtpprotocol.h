/*
 *  File: mtpprotocol.h
 *  Created: Tuesday, December 28, 2004
 *  Time-stamp: <30/12/2004 12:56:00 Yann Hodique>
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

#ifndef _MTPPROTOCOL_H_
#define _MTPPROTOCOL_H_

#include <QObject>
#include <QQueue>
#include <QRegExp>

class QTcpSocket;

class MtpProtocol : public QObject {

    Q_OBJECT

public:
    MtpProtocol(QObject *parent = 0);
    ~MtpProtocol();

    void setHost(const QString& h) {host = h;}
    void setPort(Q_UINT16 p) {port = p;}
    void setLogin(const QString& l) {login = l;}
    void setPasswd(const QString& p) {passwd = p;}

    bool lineAvailable() const;
    QString readLine();

public slots:
    void connectToHost();
    void reconnectToHost();
    void writeLine(const QString&);

signals:
    void beepSignal();
    void cmdSignal(int cmd);
    void readyRead();
    void passwdQuery();

private slots:
    void readSocket();
    void writeSocket(const QString& s);

private:
    void installSocket(QTcpSocket*);
    void uninstallSocket(QTcpSocket*);

    QTcpSocket *socket;
    QString host;
    Q_UINT16 port;
    QString login;
    QString passwd;

    QChar IAC;
    QRegExp cmd_reg;

    QQueue<QString> lines;
    QString suspended;
};	// end of class MtpProtocol


#endif /* _MTPPROTOCOL_H_ */
