/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _QMTP_H_
#define _QMTP_H_

#include "qnet_base.h"

#include <qdom.h>
#include <qmap.h>
#include <qdir.h>

#include <qsyntaxhighlighter.h>

class ErrorHighlighter : public QSyntaxHighlighter {
public:

    ErrorHighlighter(QTextEdit *edit) : QSyntaxHighlighter(edit) {}

    virtual int highlightParagraph(const QString &text, int) {
        if (text.startsWith("###"))
            setFormat(0,text.length(),QColor("red"));
        return 0;
    }
};

class QProcess;
class ChatSession;
class MtpSettings;
class MtpFiltersSettings;
class UrlSettings;
class Page;
class RemoteControlServerInfo;
class QSocket;

#define DEFAULT_RC_PATH (QDir::homeDirPath() + "/.qnetrc")

/**
 *
 * Yann Hodique
 **/
class QMtp : public QMtp_base {
    Q_OBJECT

    friend class RemoteControlServerInfo;

public:

    QMtp(QWidget *parent = 0, const char *name = 0, const QString& rcpath = QString::null);
    ~QMtp();

    bool loadConfigFile();
    bool saveConfigFile();
    Page * getNewPage(const QString&, const QString&, ChatSession *, bool pop = true);
    QString iconPath();
    QString rcPath() {
        return (m_rcpath.isNull()?(DEFAULT_RC_PATH):m_rcpath);
    }

signals:
    void closeProgram();

public slots:
    void slotConfigure();
    void slotStoreConfig();
    void fileNew();
    void fileSaveAs();
    void fileExit();
    void closeCurrentTab();
    void closeTab(QWidget *);
    void slotTextDisplayed(QWidget* w);
    void slotCurrentPageChanged(QWidget* w);
    void slotDisplayFortune();
    void readFortune();
    void endFortune();

    bool loadPlugin(const QString&);
    bool unloadPlugin(const QString&);

    void refreshMenu();
    void loadStyleSheet();

    void returnPressed();
    void displayOut();
    void displayErr();

private:
    QDomDocument m_document;
    QDomDocument temporary_dom;
    QMap<QWidget*,ChatSession*> tab_map;
    QMap<QString,void*> plugins_map;
    QMap<QString,QString> plugins_name_map;
    QValueList<ChatSession*> sessions;
    QTextBrowser *fortune_page;
    QProcess *fproc;
    QPopupMenu *new_menu;
    RemoteControlServerInfo *rctl;
    QString m_rcpath;
    MtpSettings *m_settings;
    QSocket *out, *err;
    ErrorHighlighter *highlighter;

public slots:
    void launchSession(const QString& name);
    void launchSession(int index);
    void loadPlugins();
    void unloadPlugins();
    void reloadPlugins(const QStringList&);

public:
    int sessionsNumber() {return sessions.size();}
    ChatSession *session(uint i) {return (i<sessions.size()) ? sessions[i] : 0;}

};

#endif
