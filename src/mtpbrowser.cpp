/*  Time-stamp: <07/02/2005 21:22:36 Yann Hodique>  */

/**
 *  @file mtpbrowser.cpp
 *  @date Thursday, December 30, 2004
 *  @author Yann Hodique <Yann.Hodique@lifl.fr>
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
}

MtpBrowser::~MtpBrowser() {}

void MtpBrowser::display(const QString& str) {
    Mode *m = Mode::getMode(this);
    block = m->getFontLock()->highlightParagraph(str,block,cursor);
    ensureCursorVisible();
}
