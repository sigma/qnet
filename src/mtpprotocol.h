/*
 *  File: mtpprotocol.h
 *  Created: Tuesday, December 28, 2004
 *  Time-stamp: <20/01/2005 20:36:50 Yann Hodique>
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

class QIODevice;

class MtpProtocol : public QObject {

    Q_OBJECT

public:
    MtpProtocol(QObject *parent = 0);
    ~MtpProtocol();

    bool lineAvailable() const;
    QString readLine();

    void installIO(QIODevice*);
    void uninstallIO();

public slots:
    void writeLine(const QString&);

signals:
    void beepSignal();
    void cmdSignal(int cmd);
    void passwdQuery();
    void loginQuery();
    void readyRead();

private slots:
    void readIO();
    void writeIO(const QString& s);

private:
    QIODevice *io;

    QChar IAC;
    QRegExp cmd_reg;

    QQueue<QString> lines;
    QString suspended;
};	// end of class MtpProtocol


#endif /* _MTPPROTOCOL_H_ */
