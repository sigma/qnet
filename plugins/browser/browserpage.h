/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _BROWSERPAGE_H_
#define _BROWSERPAGE_H_

#include "page.h"

class MtpBrowser;
class QGridLayout;

/**
 *
 * Yann Hodique
 **/
class BrowserPage : public Page {
    Q_OBJECT

public:
    BrowserPage(QWidget *parent, const char *name, Master * session);
    ~BrowserPage();
    void append(const QString & msg);
    MtpBrowser* chat_view;
    QString getText();

protected:
    QGridLayout* BrowserPageBaseLayout;

protected slots:
    virtual void languageChange();
};

#endif
