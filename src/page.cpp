/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "page.h"


Page::Page(QWidget *parent, const char *name, ChatSession * master)
  : QWidget(parent, name)
{
m_master = master;
}


Page::~Page()
{
}

//void Page::append(QString & msg) {}

ChatSession * Page::getMaster() {
return m_master;
}
