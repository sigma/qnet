/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "SessionsSettings.h"

#include <qlistbox.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qinputdialog.h>

SessionsSettings::SessionsSettings(QWidget *parent, const char *name)
        : SessionsSettingsBase(parent, name) {}


SessionsSettings::~SessionsSettings() {}

void SessionsSettings::addSessionItem(SessionItem & it, int index) {
    map.insert(it.name,it);
    sessions_box->insertItem(it.name, index);
}

void SessionsSettings::delSessionItem(const QString& name) {
    map.remove(name);
}

void SessionsSettings::slotSubs() {
    SessionItem *it = &(*(map.find(sessions_box->currentText())));
    if (it->name != name_edit->text())
        return;
    it->host = host_edit->text();
    it->port = port_edit->text();
    it->login = login_edit->text();
    it->password = pass_edit->text();
    it->autoconnect = auto_check->isChecked();
}

void SessionsSettings::slotAdd() {
    bool ok;
    QString name = QInputDialog::getText("Session name","Enter a name",QLineEdit::Normal,("session"),&ok,this);
    if(ok) {
        SessionItem it(name);
        addSessionItem(it);
    }
}

void SessionsSettings::slotDel() {
    delSessionItem(QString(sessions_box->currentText()));
    sessions_box->removeItem(sessions_box->currentItem());
}

void SessionsSettings::slotDown() {
    unsigned int index = sessions_box->currentItem();

    if (index < sessions_box->count()) {
        QString text = sessions_box->currentText();
        sessions_box->removeItem(index);
        sessions_box->insertItem(text,index + 1);
    }
}

void SessionsSettings::slotUp() {
    int index = sessions_box->currentItem();
    if (index) {
        QString text = sessions_box->currentText();
        sessions_box->removeItem(index);
        sessions_box->insertItem(text,index - 1);
    }
}

void SessionsSettings::slotUpdateInfo(const QString & name) {
    SessionItem it = *(map.find(name));
    name_edit->setText(it.name);
    host_edit->setText(it.host);
    port_edit->setText(it.port);
    login_edit->setText(it.login);
    pass_edit->setText(it.password);
    auto_check->setChecked(it.autoconnect);
}
