/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "mtpbrowser.h"


MtpBrowser::MtpBrowser(QWidget *parent, const char *name)
  : QTextBrowser(parent, name)
{
}


MtpBrowser::~MtpBrowser()
{
}

void MtpBrowser::setSource(const QString &) {}
