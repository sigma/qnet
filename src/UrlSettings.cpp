/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "UrlSettings.h"

#include <qlistbox.h>
#include <qlineedit.h>

UrlSettings::UrlSettings(QWidget *parent, const char *name)
        : UrlSettingsBase(parent, name) {}


UrlSettings::~UrlSettings() {}

void UrlSettings::addUrlItem(UrlItem & it) {
    map.insert(it.name,it);
    urls_box->insertItem(it.name);
}

void UrlSettings::delUrlItem(const QString& name) {
    map.remove(name);
}

void UrlSettings::slotAdd() {
    if (name_edit->text().length() && prefix_edit->text().length() && command_edit->text().length()) {
        UrlItem it(name_edit->text(),prefix_edit->text(),command_edit->text());
        addUrlItem(it);
    }
}

void UrlSettings::slotDel() {
    delUrlItem(QString(urls_box->currentText()));
    urls_box->removeItem(urls_box->currentItem());
}


void UrlSettings::slotUpdateInfo(const QString & name) {
    UrlItem it = *(map.find(name));
    name_edit->setText(it.name);
    prefix_edit->setText(it.prefix);
    command_edit->setText(it.command);
}
