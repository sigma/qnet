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

#include <qwidget.h>
#include <qdom.h>
#include <vector>

#include "chatpage.h"
#include "version.h"
#include "master.h"

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

class ChatSession : public ChatPage {
    Q_OBJECT

public:
    ChatSession(const QString& session_name, QMtp * mtp, QWidget *parent, const char *name,QDomDocument * dom);
    ~ChatSession();

    void displayStderr(const QString&);
    void displayStdout(const QString&);
    const QString & sessionName() const;
    QMtp* topLevel() const;
    
    void updateFilters();

public slots:
    void returnPressed();
    void closeSession();
    void slotLinkClicked(const QString &);
    void slotComplete();
    void slotReconnect();

    void slotUserDoubleClicked(QListBoxItem*);
        
    void setDomDocument(QDomDocument * dom);
    void kill(Page*);
    void send(const QString &);
    
private:
    void escape(QString * msg);
    void unescape(QString * msg);
    bool filter(QString * msg);
    void getInfo();

    QString caseUnsensitive(const QString& msg);    

    void executeShellCommand(const QString&);
    void createTelnetManager();
    
    QProcess * proc;

    QMtp * mtp;
    TelnetManager * mng;
    QString login;
    bool login_set;
    bool enable_stdout;
    bool who_demanded;
    bool receiving_who;
    int position;

    QString host, port, session_name;

    QAction *complete, *reconnect;
    
    QDomDocument * m_dom;
    MtpFilter * m_filter;
//    MtpContext * m_context;
    std::vector<Page *> brothers;
    
private slots:
	void deleteProcess();

};

#endif
