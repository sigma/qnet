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

#include "chatpage.h"

/**
 *
 * Yann Hodique
 **/
class TellPage : public ChatPage {
    Q_OBJECT

public:
    TellPage(QWidget *parent, const char *name, Master * session);
    ~TellPage();
    void setPrefix(const QString&);
    QString getText();

public slots:
    virtual void returnPressed();

private:
    QString prefix;

};

#endif
