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

#include <qwidget.h>
#include "qnet_base.h"
#include <qdom.h>
#include <qmap.h>
#include <qprocess.h>

class ChatSession;
class MtpSettings;
class MtpFiltersSettings;
class UrlSettings;
class Page;
class RemoteControlServerInfo;

/**
 * 
 * Yann Hodique
 **/
class QMtp : public QMtp_base {
    Q_OBJECT

    friend class RemoteControlServerInfo;
    
public:

    typedef enum {
        TELL,
        BROWSER,
	DRAWING
    } PageType;

    QMtp(QWidget *parent = 0, const char *name = 0);
    ~QMtp();

    bool loadConfigFile();
    bool saveConfigFile();
    Page * getNewPage(PageType, QString, ChatSession *);

public slots:
    void slotConfigure();
    void fileNew();
    void fileSessions();
    void fileExit();
    void closeCurrentTab();
    void closeTab(QWidget *);
    void gotoPreviousTab();
    void gotoNextTab();
    void helpAbout();
    void slotTextDisplayed(QWidget* w);
    void slotCurrentPageChanged(QWidget* w);
    void slotDisplayFortune();
    void readFortune();
    void endFortune();

private:
    QDomDocument m_document;
    QMap<QWidget*,ChatSession*> tab_map;
    QValueList<ChatSession*> sessions;
    QTextBrowser *fortune_page;
    QProcess *fproc;
    
    RemoteControlServerInfo *rctl;
    
private:
	void launchSession(QString name);
};

#endif
