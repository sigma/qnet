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
class QAction;
class QString;
class QStringList;
class QStyleSheetItem;
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
    ChatSession(QString session_name, QMtp * mtp, QWidget *parent, const char *name,QDomDocument * dom);
    ~ChatSession();

    void displayStderr(QString);
    void displayStdout(QString);
    const QString & sessionName();
    QMtp* topLevel();

public slots:
    void returnPressed();
    void closeSession();
    void slotLinkClicked(const QString &);
    void slotHistoryUp();
    void slotHistoryDown();
    void slotNewLine();
    void slotComplete();
    void slotReconnect();

    void setDomDocument(QDomDocument * dom);
    void kill(Page*);
    void send(QString &);

private:

    void applyFilters();
    void applyLine(QString,QString,QString);
    void applyItem(QString,QString,QString);
    void escape(QString * msg);
    bool filter(QString * msg);
    void getInfo();

    QString caseUnsensitive(QString msg);
    
    void removeUser(QString);
    void addUser(QString);

    void executeShellCommand(QString);
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

    QString doc_source;

    QStyleSheetItem *item;
    QAction *history_up, *history_down, *new_line, *complete, *reconnect;
    QStringList history;
    QStringList::Iterator history_iterator;
    QString host, port, session_name;

    QDomDocument * m_dom;
    MtpFilter * m_filter;
    MtpContext * m_context;
    std::vector<Page *> brothers;

signals:
	void textDisplayed(QWidget *);
private slots:
	void deleteProcess();
signals:
	void outputMessage(const QString& );
};

#endif
