/*
 *  File: MainChatPage.h
 *  Created: Wednesday, April 14, 2004
 *  Time-stamp: <14/04/2004 14:09:12 Yann Hodique>
 *  Copyright: Yann Hodique
 *  Email: Yann.Hodique@lifl.fr
 */

/************************************************************************
 *                                                                      *
 * This program is free software; you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 ************************************************************************/

#ifndef _MAINCHATPAGE_H_
#define _MAINCHATPAGE_H_

#include "chatpage.h"
#include <qaction.h>

class MainChatPage : public ChatPage {
    Q_OBJECT

public:
    MainChatPage(QWidget *parent = 0, const char *name = 0, Master *master = 0);
    ~MainChatPage();

public slots:
    void returnPressed();
    void slotComplete();
    void slotReconnect();
    void slotUserDoubleClicked(QListBoxItem*);
private:
    QAction *complete, *reconnect;
};


#endif /* _MAINCHATPAGE_H_ */
