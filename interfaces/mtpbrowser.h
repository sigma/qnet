/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _MTPBROWSER_H_
#define _MTPBROWSER_H_

#include <qwidget.h>
#include <qstring.h>
#include <qtextbrowser.h>

/**
 * 
 * Yann Hodique
 **/
class MtpBrowser : public QTextBrowser
{
  Q_OBJECT

public:
    MtpBrowser(QWidget *parent, const char *name) : QTextBrowser(parent,name) {
	setTextFormat(Qt::RichText);
    }
    ~MtpBrowser() {}

    QString getText() { return text();}
    
public slots:
    void setSource(const QString &) {}
};

#endif
