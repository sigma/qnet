/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "remotecontrol.h"
#include "version.h"
#include "qnet.h"
#include "ChatSession.h"
#include "domutil.h"

#include <qregexp.h>
#include <qmessagebox.h>

RemoteControlClientSocket::RemoteControlClientSocket(int sock, QObject *parent, const char *name) :
QSocket( parent, name ) {
    line = 0;
    connect( this, SIGNAL(readyRead()),
             SLOT(readClient()) );
    connect( this, SIGNAL(connectionClosed()),
             SLOT(deleteLater()) );
    setSocket( sock );
}

RemoteControlClientSocket::~RemoteControlClientSocket() {}

void RemoteControlClientSocket::readClient() {
    QTextStream ts( this );
    while ( canReadLine() ) {
        QString str = ts.readLine();
        emit logText( tr("Read: '%1'\n").arg(str) );
        emit processText(str);

        line++;
    }
}


RemoteControlSimpleServer::RemoteControlSimpleServer(int port, QObject* parent) :
QServerSocket( port, 1, parent ) {
    if ( !ok() ) {
        QMessageBox::critical(0,"Error","Failed to bind to port " + QString::number(port));
    }
}

RemoteControlSimpleServer::~RemoteControlSimpleServer() {}

void RemoteControlSimpleServer::newConnection( int socket ) {
    RemoteControlClientSocket *s = new RemoteControlClientSocket( socket, this );
    emit newConnect( s );
}



RemoteControlServerInfo::RemoteControlServerInfo(QMtp * mtp, int port, QTextBrowser *log, const QString & pass) {
    RemoteControlSimpleServer *server = new RemoteControlSimpleServer(port, this );

    m_mtp = mtp;
    infoText = log;
    remote_pass = pass;
    connect( server, SIGNAL(newConnect(RemoteControlClientSocket*)),
             SLOT(newConnect(RemoteControlClientSocket*)) );

    // Commands :
    commands.insert("list",&RemoteControlServerInfo::listCommand);
    commands.insert("exit",&RemoteControlServerInfo::exitCommand);
    commands.insert("commands",&RemoteControlServerInfo::commandsCommand);
    commands.insert("send",&RemoteControlServerInfo::sendCommand);
    commands.insert("sync",&RemoteControlServerInfo::synchroCommand);
    commands.insert("desync",&RemoteControlServerInfo::desynchroCommand);
    commands.insert("connect",&RemoteControlServerInfo::connectCommand);
    commands.insert("disconnect",&RemoteControlServerInfo::disconnectCommand);
}

RemoteControlServerInfo::~RemoteControlServerInfo() {}

void RemoteControlServerInfo::newConnect( RemoteControlClientSocket *s ) {
    infoText->append( tr("New connection\n") );

    QTextStream(s) << "Welcome to " CLIENT " remote administration tool\nType \"exit\" to leave\n";

    if(remote_pass != QString::null) {
        connect (s, SIGNAL(processText(const QString&)),
                 SLOT(auth(const QString&)));
	QTextStream(s) << "Authenfication required\nPassword : ";
    }
    else {
        connect( s, SIGNAL(logText(const QString&)),
                 infoText, SLOT(append(const QString&)) );
        connect( s, SIGNAL(processText(const QString&)),
                 SLOT(processText(const QString&)));
    }
    connect( s, SIGNAL(connectionClosed()),
             SLOT(connectionClosed()) );

    map.insert((int)s,s);
}

void RemoteControlServerInfo::auth(const QString & txt) {
    if(txt == remote_pass) {
        disconnect(sender(),SIGNAL(processText(const QString&)),
                   this,SLOT(auth(const QString&)));
        connect( sender(), SIGNAL(logText(const QString&)),
                 infoText, SLOT(append(const QString&)) );
        connect( sender(), SIGNAL(processText(const QString&)),
                 SLOT(processText(const QString&)));
    } else
        QTextStream((RemoteControlClientSocket*)sender()) << "Incorrect Password\nPassword : ";
}

void RemoteControlServerInfo::display(const QString& msg) {
    ChatSession *session = (ChatSession*)sender();
    SyncMap::Iterator it;
    if((it = sync_map.find(session)) != sync_map.end()) {
	for(QValueList<RemoteControlClientSocket*>::Iterator iterator = (*it).begin(); iterator != (*it).end(); ++ iterator)
	    QTextStream(*iterator) << session->sessionName() << ": " << msg << endl;
    }
}

void RemoteControlServerInfo::connectionClosed() {
    infoText->append( tr("Client closed connection\n") );
    map.remove((int)sender());
}

void RemoteControlServerInfo::processText(const QString & txt) {
    RemoteControlClientSocket* socket = (RemoteControlClientSocket*)sender();

    bool ok(false);
    QRegExp reg("(\\w+)( .*)?");
    if(reg.exactMatch(txt)) {
	QString command = reg.cap(1);
	CommandMap::Iterator it;
	if((it = commands.find(command)) != commands.end()) { // found suitable command
	    ok = true;
	    (this->*(it.data()))(socket,txt);
	}
    }
    if (!ok) unknownCommand(socket,txt);
}

void RemoteControlServerInfo::listCommand(RemoteControlClientSocket *socket,const QString& txt) {
    QRegExp re("\\w+ +(\\w+) *");
    QTextStream stream(socket);
    if(re.exactMatch(txt)) {
	QString command = re.cap(1);
	if(command == "active") {
	    stream << "Listing active sessions" << endl;
	    for (QValueList<ChatSession*>::Iterator it = m_mtp->sessions.begin(); it != m_mtp->sessions.end(); ++it) {
		stream << "list : " << (*it)->sessionName() << endl;
	    }
	}
	else if(command == "all") {
	    stream << "Listing all sessions" << endl;
	    QStringList list = DomUtil::readListEntry(m_mtp->m_document,"/general/sessions","session");
	    for (QStringList::Iterator it = list.begin(); it != list.end(); ++it)
		stream << "list : " << (*it) << endl;
	}
	else if(command == "shared") {}
	else stream << "Unrecognized option \"" << command << "\"" << endl;
    }
    else stream << "Syntax error using command \"list\"" << endl;
}

void RemoteControlServerInfo::exitCommand(RemoteControlClientSocket *socket,const QString&) {
    socket->close();
}

void RemoteControlServerInfo::commandsCommand(RemoteControlClientSocket *socket,const QString&) {
    QTextStream stream(socket);
    for(CommandMap::Iterator it = commands.begin(); it != commands.end(); ++it)
	stream << "commands : " << it.key() << endl;
}

void RemoteControlServerInfo::sendCommand(RemoteControlClientSocket *socket,const QString& txt) {
    QRegExp re("\\w+ +(\\w+) +([^ ].*)");
    QTextStream stream(socket);
    if(re.exactMatch(txt)) {
	QString session = re.cap(1);
	QValueList<ChatSession*>::Iterator it;
	bool ok(false);
	for(it = m_mtp->sessions.begin(); it != m_mtp->sessions.end(); ++it) {
	    if((*it)->sessionName() == session) {
		ok = true;
		QString message = re.cap(2);
		(*it)->send(message);
		break;
	    }
	}
	if (!ok) stream << "Session \"" << session << "\" does not exist" << endl;
    }
    else
	stream << "Syntax error using command \"send\"" << endl;
}

void RemoteControlServerInfo::synchroCommand(RemoteControlClientSocket *socket,const QString& txt) {
    QRegExp re("\\w+ +(\\w+) *");
    QTextStream stream(socket);
    if(re.exactMatch(txt)) {
	QString session = re.cap(1);
	QValueList<ChatSession*>::Iterator it;
	bool ok(false);
	for(it = m_mtp->sessions.begin(); it != m_mtp->sessions.end(); ++it) {
	    if((*it)->sessionName() == session) {
		stream << "Synchro with session \"" << session << "\"" << endl;
		SyncMap::Iterator iterator;
		if((iterator = sync_map.find(*it)) == sync_map.end()) {
		    QValueList<RemoteControlClientSocket*> list;
		    list.append(socket);
		    sync_map.insert(*it,list);
		    connect(*it,SIGNAL(outputMessage(const QString&)),
			    this, SLOT(display(const QString&)));
		}
		else
		    (*iterator).append(socket);
		ok = true;
		break;
	    }
	}
	if (!ok) stream << "Session \"" << session << "\" does not exist" << endl;
    }
    else
	stream << "Syntax error using command \"sync\"" << endl;
}

void RemoteControlServerInfo::desynchroCommand(RemoteControlClientSocket *socket,const QString& txt) {
    QRegExp re("\\w+ +(\\w+) *");
    QTextStream stream(socket);
    if(re.exactMatch(txt)) {
	QString session = re.cap(1);
	QValueList<ChatSession*>::Iterator it;
	bool ok(false);
	for(it = m_mtp->sessions.begin(); it != m_mtp->sessions.end(); ++it) {
	    if((*it)->sessionName() == session) {
		stream << "Desynchro with session \"" << session << "\"" << endl;
		sync_map.remove(*it);
		if(sync_map.begin() == sync_map.end()) {
		    disconnect(*it,SIGNAL(outputMessage(const QString&)),
			       this, SLOT(display(const QString&)));
		}
		ok = true;
		break;
	    }
	}
	if (!ok) stream << "Session \"" << session << "\" does not exist" << endl;
    }
    else
	stream << "Syntax error using command \"desync\"" << endl;
}

void RemoteControlServerInfo::connectCommand(RemoteControlClientSocket *socket,const QString& txt) {
    QRegExp re("\\w+ +(\\w+) *");
    QTextStream stream(socket);
    if(re.exactMatch(txt)) {
	QString session = re.cap(1);
	bool ok(false);
	QStringList list = DomUtil::readListEntry(m_mtp->m_document,"/general/sessions","session");
	for (QStringList::Iterator it = list.begin(); it != list.end(); ++it)
	    if((*it) == session) {
		stream << "Connect session \"" << session << "\"" << endl;
		m_mtp->launchSession(session);
		ok = true;
		break;
	    }
	if (!ok) stream << "Session \"" << session << "\" does not exist" << endl;
    }
    else
	stream << "Syntax error using command \"connect\"" << endl;
}

void RemoteControlServerInfo::disconnectCommand(RemoteControlClientSocket *socket,const QString& txt) {
    QRegExp re("\\w+ +(\\w+) *");
    QTextStream stream(socket);
    if(re.exactMatch(txt)) {
	QString session = re.cap(1);
	QValueList<ChatSession*>::Iterator it;
	bool ok(false);
	for(it = m_mtp->sessions.begin(); it != m_mtp->sessions.end(); ++it) {
	    if((*it)->sessionName() == session) {
            ok = true;
            m_mtp->closeTab((*it)->chatpage());
            break;
	    }
	}
	if (!ok) stream << "Session \"" << session << "\" does not exist" << endl;
    }
    else
	stream << "Syntax error using command \"send\"" << endl;
}

void RemoteControlServerInfo::unknownCommand(RemoteControlClientSocket *socket, const QString& txt) {
    QTextStream(socket) << "Unknown command \"" << txt << "\"" << endl;
}
