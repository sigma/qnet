/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "PrefixSettings.h"

#include <qlistbox.h>
#include <qlineedit.h>

PrefixSettings::PrefixSettings(QWidget *parent, const char *name)
  : PrefixSettingsBase(parent, name)
{
}


PrefixSettings::~PrefixSettings()
{
}

void PrefixSettings::addPrefixItem(PrefixItem & it) {
map.insert(it.name,it);
prefix_box->insertItem(it.name);
}

void PrefixSettings::delPrefixItem(QString name) {
map.remove(name);
}

void PrefixSettings::slotAdd() {
if (name_edit->text().length()) {
PrefixItem it(name_edit->text());
	addPrefixItem(it);
        }
}

void PrefixSettings::slotDel() {
delPrefixItem(QString(prefix_box->currentText()));
prefix_box->removeItem(prefix_box->currentItem());
}
