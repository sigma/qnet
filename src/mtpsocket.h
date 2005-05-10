/*  Time-stamp: <09/05/2005 17:29:06 Yann Hodique>  */

/**
 *  @file mtpsocket.h
 *  @date Thursday, January 20, 2005
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

#ifndef _MTPSOCKET_H_
#define _MTPSOCKET_H_

#include <QTcpSocket>

#include "interactiveiodevice.h"

class MtpSocket: public QTcpSocket, public InteractiveIODevice {

    Q_OBJECT

public:
    MtpSocket(QObject *parent = 0);
    ~MtpSocket();

    void setHost(const QString& h) {host = h;}
    void setPort(int p) {port = p;}
    void setLogin(const QString& l) {login = l;}
    void setPasswd(const QString& p) {passwd = p;}

    QString getLogin() const {return login;}
    QString getPasswd() const {return passwd;}

public slots:
    void connectToHost();
    void sendLogin();
    void sendPasswd();

private:
    QString host;
    int port;
    QString login;
    QString passwd;

};	// end of class MtpSocket


#endif /* _MTPSOCKET_H_ */
