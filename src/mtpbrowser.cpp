/*
 *  File: mtpbrowser.cpp
 *  Created: Thursday, December 30, 2004
 *  Time-stamp: <02/01/2005 11:58:19 Yann Hodique>
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

#include "mtpbrowser.h"
#include "mode.h"
#include "fontlock.h"

MtpBrowser::MtpBrowser(QWidget * parent): QTextBrowser(parent), cursor(document()) {
    block = 0;
    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sp.setHorizontalStretch(100);
    sp.setVerticalStretch(100);
    setSizePolicy(sp);
    setMinimumSize( QSize( 1, 1 ) );
}

MtpBrowser::~MtpBrowser() {}

void MtpBrowser::display(const QString& str) {
    Mode *m = Mode::getMode(this);
    block = m->getFontLock()->highlightParagraph(str,block,cursor);
    ensureCursorVisible();
}
