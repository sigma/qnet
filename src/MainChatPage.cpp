/*
 *  File: MainChatPage.cpp
 *  Created: Wednesday, April 14, 2004
 *  Time-stamp: <14/04/2004 14:12:30 Yann Hodique>
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

#include "MainChatPage.h"

#include <qtextedit.h>
#include <qlistbox.h>

MainChatPage::MainChatPage(QWidget *parent, const char *name, Master *master) :
        ChatPage(parent,name,master) {
    complete = new QAction(chat_edit,"complete");
    complete->setAccel(QKeySequence(Key_Tab));
    reconnect = new QAction(this,"reconnect");
    reconnect->setAccel(QKeySequence(CTRL + Key_R));
    connect(complete, SIGNAL(activated()),
            this, SLOT(slotComplete()));
    connect(reconnect, SIGNAL(activated()),
            this, SLOT(slotReconnect()));

    chat_edit->setUndoRedoEnabled(false);
}

MainChatPage::~MainChatPage() {}


void MainChatPage::returnPressed() {
    // delete this $#!@? "\n" we've just inserted
    chat_edit->doKeyboardAction(QTextEdit::ActionBackspace);

    // put in history if and ONLY if password is already set...
    if (getMaster()->isLogged() && (chat_edit->text() != history[0]))
        history.push_front(chat_edit->text());

    QString m(chat_edit->text());
    getMaster()->send(m);
    chat_edit->clear();

    // history returns to start
    history_iterator = 0;

}

void MainChatPage::slotComplete() {
    int para, index;
    //    chat_edit->doKeyboardAction(QTextEdit::ActionBackspace);
    chat_edit->getCursorPosition(&para,&index);
    QString parag = chat_edit->text(para);
    QString pref;

    if (!parag.at(index-1).isLetterOrNumber())
        return;

    while (parag.at(--index).isLetterOrNumber()) {
        pref = parag.at(index) + pref;
        chat_edit->doKeyboardAction(QTextEdit::ActionBackspace);
    }
    for(uint i=0; i<users_box->count(); i++)
        //if (users_box->text(i).startsWith(pref)) {
        if (!(users_box->text(i).find(pref,0,false))) {
            if (users_box->text(i) == pref) {
                uint position = (i+1)%(users_box->count());
                chat_edit->insertAt(users_box->text(position),para,++index);
                chat_edit->setCursorPosition(para,index+users_box->text(position).length());
            } else {
                chat_edit->insertAt(users_box->text(i),para,++index);
                chat_edit->setCursorPosition(para,index+users_box->text(i).length());
            }
            return;
        }
    chat_edit->insertAt(pref,para,++index);
    chat_edit->setCursorPosition(para,index+pref.length());
}

void MainChatPage::slotUserDoubleClicked(QListBoxItem* item) {
    if(!item) return;
    getMaster()->displayStdout(":tell:" + item->text() +": ");
}

void MainChatPage::slotReconnect() {
    getMaster()->slotReconnect();
}
