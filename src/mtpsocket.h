/*
 *  File: mtpsocket.h
 *  Created: Thursday, January 20, 2005
 *  Time-stamp: <20/01/2005 22:06:39 Yann Hodique>
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

#ifndef _MTPSOCKET_H_
#define _MTPSOCKET_H_

#include <QTcpSocket>

class MtpSocket: public QTcpSocket {

    Q_OBJECT

public:
    MtpSocket(QObject *parent = 0);
    ~MtpSocket();

    void setHost(const QString& h) {host = h;}
    void setPort(Q_UINT16 p) {port = p;}
    void setLogin(const QString& l) {login = l;}
    void setPasswd(const QString& p) {passwd = p;}

    QString getLogin() {return login;}
    QString getPasswd() {return passwd;}

public slots:
    void connectToHost();
    void sendLogin();
    void sendPasswd();

private:
    QString host;
    Q_UINT16 port;
    QString login;
    QString passwd;

};	// end of class MtpSocket


#endif /* _MTPSOCKET_H_ */
