/****************************************************************************
**
** Copyright (C) 2002 Yann Hodique <Yann.Hodique@lifl.fr>
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#ifndef _REMOTECONTROL_H_
#define _REMOTECONTROL_H_

#include <qsocket.h>
#include <qserversocket.h>
#include <qtextbrowser.h>
#include <qmap.h>

#include <stdlib.h>

class QMtp;
class ChatSession;

/*
  The ClientSocket class provides a socket that is connected with a client.
  For every client that connects to the server, the server creates a new
  instance of this class.
*/
class RemoteControlClientSocket : public QSocket {
    Q_OBJECT

public:
    RemoteControlClientSocket( int sock, QObject *parent=0, const char *name=0 );
    ~RemoteControlClientSocket();

signals:
    void logText( const QString& );
    void processText(const QString& );

private slots:
    void readClient();

private:
    int line;
};


/*
  The SimpleServer class handles new connections to the server. For every
  client that connects, it creates a new ClientSocket -- that instance is now
  responsible for the communication with that client.
*/
class RemoteControlSimpleServer : public QServerSocket {
    Q_OBJECT

public:
    RemoteControlSimpleServer( int port, QObject* parent=0 );
    ~RemoteControlSimpleServer();

public slots:
    void newConnection( int socket );

signals:
    void newConnect( RemoteControlClientSocket* );
};


/*
  The ServerInfo class provides a small GUI for the server. It also creates the
  SimpleServer and as a result the server.
*/
class RemoteControlServerInfo : QObject {
    Q_OBJECT

    typedef QMap<QString, void(RemoteControlServerInfo::*)(RemoteControlClientSocket*,const QString&)> CommandMap;
    typedef QMap<ChatSession*,QValueList<RemoteControlClientSocket*> > SyncMap;

public:
    RemoteControlServerInfo(QMtp *, int port, QTextBrowser *log, const QString & pass = QString::null);
    ~RemoteControlServerInfo();

private slots:
    void newConnect( RemoteControlClientSocket *s );
    void connectionClosed();
    void processText(const QString & txt);
    void auth(const QString&);
    void display(const QString&);

    void listCommand(RemoteControlClientSocket*,const QString&);
    void commandsCommand(RemoteControlClientSocket*,const QString&);
    void exitCommand(RemoteControlClientSocket*,const QString&);
    void sendCommand(RemoteControlClientSocket*,const QString&);
    void synchroCommand(RemoteControlClientSocket*,const QString&);
    void desynchroCommand(RemoteControlClientSocket*,const QString&);
    void connectCommand(RemoteControlClientSocket*,const QString&);
    void disconnectCommand(RemoteControlClientSocket*,const QString&);
    void unknownCommand(RemoteControlClientSocket*,const QString&);

private:
    QTextBrowser *infoText;
    QMap<int,RemoteControlClientSocket*> map;
    SyncMap sync_map;
    CommandMap commands;

    QString remote_pass;
    QMtp * m_mtp;
};

#endif
