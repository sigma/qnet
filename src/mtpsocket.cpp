/*  Time-stamp: <09/02/2005 20:49:34 Yann Hodique>  */

/**
 *  @file mtpsocket.cpp
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

#include "mtpsocket.h"

MtpSocket::MtpSocket(QObject *parent) : QTcpSocket(parent), InteractiveIODevice(parent) {
    host = QString::null;
    port = 0;
    login = QString::null;
    passwd = QString::null;
}

MtpSocket::~MtpSocket() {}

void MtpSocket::connectToHost() {
    if(host != QString::null && port != 0) {
        QTcpSocket::connectToHost(host,port);
    }
}

void MtpSocket::sendLogin() {
    if(login != QString::null)
        write((login + "\r\n").toAscii());
}

void MtpSocket::sendPasswd() {
    if(passwd != QString::null)
        write((passwd + "\r\n").toAscii());
}
