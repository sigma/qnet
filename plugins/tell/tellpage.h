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
#include <qaction.h>
#include <qstringlist.h>

#include "page.h"
#include "master.h"

class QTextEdit;
class MtpBrowser;
class QGridLayout;

/**
 * 
 * Yann Hodique
 **/
class TellPage : public Page {
    Q_OBJECT

public:
    TellPage(QWidget *parent, const char *name, Master * session);
    ~TellPage();
    virtual void append(const QString & msg);
    void setPrefix(const QString&);
    QTextEdit* chat_edit;
    MtpBrowser* chat_view;

    QString getText();
    
public slots:
    virtual void returnPressed();
    void slotHistoryUp();
    void slotHistoryDown();
    void slotNewLine();
    void slotPageUp();
    void slotPageDown();

protected:
    QGridLayout* TellPageBaseLayout;

protected slots:
    virtual void languageChange();

private:
    QString prefix;
    QAction *history_up, *history_down, *new_line, *pgup, *pgdown;
    QStringList history;
    QStringList::Iterator history_iterator;

};

#endif
