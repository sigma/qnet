/*
 *  File: mtpprotocol.h
 *  Created: Tuesday, December 28, 2004
 *  Time-stamp: <21/01/2005 17:17:29 Yann Hodique>
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

/**
 * High level protocol for interpreting structured messages from MtpSocket
 *
 */
class MtpProtocol : public QObject {

    Q_OBJECT

public:
    /**
     * Constructor
     *
     * @param parent the parent QObject
     *
     */
    MtpProtocol(QObject *parent = 0);

    /**
     * Destructor
     *
     */
    ~MtpProtocol();

    /**
     * test if the input buffer still contains Lines
     *
     * @return true it there are lines to be read
     */
    bool lineAvailable() const;

    /**
     * read a line if possible
     *
     * @return the first available line or QString::null if none available
     */
    QString readLine();

    /**
     * Install a QIODevice for interaction between a server and the client. If
     * there is already an installed QIODevice, it is uninstalled first.
     *
     * @see MtpSocket
     *
     * @param io the QIODevice to interact with
     */
    void installIO(QIODevice* io);

    /**
     * Disconnect the current QIODevice. If none is installed, do nothing.
     *
     */
    void uninstallIO();

public slots:
    /**
     * Pass a message to the underlaying QIODevice. If QIODevice is installed, the message is lost.
     *
     * @param txt the message to send
     */
    void writeLine(const QString& txt);

signals:
    /**
     * signal emitted when the user receives a beep request
     *
     */
    void beepSignal();

    /**
     * signal emitted when a telnet command sequence is received
     *
     * @param cmd id of the command
     */
    void cmdSignal(int cmd);

    /**
     * signal emitted when the server asks for authentification password
     *
     */
    void passwdQuery();

    /**
     * signal emitted when the server asks for authentification login
     *
     */
    void loginQuery();

    /**
     * signal emitted when some messages are received from the server
     *
     */
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
