/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "tellpage.h"

#include <qlistbox.h>
#include <qtextedit.h>
#include <mtpbrowser.h>

PLUGIN_FACTORY(TellPage,"tell")

TellPage::TellPage(QWidget *parent, const char *name, Master * session)
        : ChatPage(parent,name,session) {

    setPrefix(QString("tell ") + name + " ");
    users_box->hide();
}


TellPage::~TellPage() {}

void TellPage::returnPressed() {
    // delete this $#!@? "\n" we've just inserted
    chat_edit->doKeyboardAction(QTextEdit::ActionBackspace);

    history.push_front(chat_edit->text());

    QString msg(prefix + chat_edit->text());
    this->getMaster()->send(msg);
    chat_edit->clear();

    history_iterator = 0;
}

void TellPage::setPrefix(const QString& prefix) {
    this->prefix = prefix;
}

QString TellPage::getText() {
    return chat_view->text();
}
