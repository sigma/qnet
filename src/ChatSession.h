/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _CHATSESSION_H_
#define _CHATSESSION_H_

#define CHAT_BUFFER_LENGTH 256

#include <vector>

#include "MainChatPage.h"
#include "version.h"

class QDomDocument;
class QProcess;
class QString;
class QStringList;
class TelnetManager;
class MtpSettings;
class QMtp;
class QResizeEvent;
class MtpFilter;
class MtpContext;
class Page;

#ifdef GUILE
class Scm;
#endif

class ChatSession : public Master {
    Q_OBJECT

public:
    ChatSession(const QString& session_name, QMtp * mtp, QWidget *parent, const char *name,QDomDocument * dom);
    ~ChatSession();

    void displayStderr(const QString&);
    void displayStdout(const QString&);
    const QString& sessionName() const;
    QMtp* topLevel() const;

    void updateFilters();

    MainChatPage *chatpage();

public slots:
    void closeSession();
    void slotLinkClicked(const QString&);
    void slotReconnect();
    void kill(Page*);
    void send(const QString&);
    void incoming(const QString&);
    void outgoing(const QString&);

signals:
	void outputMessage(const QString& );
    void closedSession();

private:
    void escape(QString * msg);
    void unescape(QString * msg);
    bool filter(QString * msg);

    QString caseUnsensitive(const QString& msg);

    void executeShellCommand(const QString&);
    void createTelnetManager();

    QProcess * proc;

    QMtp * mtp;
    TelnetManager * mng;

    QString host, port, session_name;

    MtpFilter * m_filter;
//    MtpContext * m_context;
    std::vector<Page *> brothers;

    MainChatPage *m_chatpage;

#ifdef GUILE
    Scm *m_scm;
#endif

private slots:
	void deleteProcess();

};

#endif
