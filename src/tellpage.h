/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _TELLPAGE_H_
#define _TELLPAGE_H_

#include <qwidget.h>
#include "page.h"
#include "ChatSession.h"
#include <qaction.h>

/**
 * 
 * Yann Hodique
 **/
class TellPage : public Page {
    Q_OBJECT

public:
    TellPage(QWidget *parent, const char *name, ChatSession * session);
    ~TellPage();
    virtual void append(QString & msg);
    void setPrefix(QString);
    QTextEdit* chat_edit;
    MtpBrowser* chat_view;

public slots:
    virtual void returnPressed();
    void slotHistoryUp();
    void slotHistoryDown();
    void slotNewLine();


protected:
    QGridLayout* TellPageBaseLayout;

protected slots:
    virtual void languageChange();

private:
    QString prefix;
    QAction *history_up, *history_down, *new_line;
    QStringList history;
    QStringList::Iterator history_iterator;

};

#endif
