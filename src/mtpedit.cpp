/*  Time-stamp: <07/02/2005 21:22:37 Yann Hodique>  */

/**
 *  @file mtpedit.cpp
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

#include "mtpedit.h"

#include <QShortcut>

#include <iostream>

MtpEdit::MtpEdit(QWidget *parent) : QTextEdit(parent) {
    setWordWrap(QTextEdit::NoWrap);

    //@todo Suppress this hardcoded shortcut
    return_pressed = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return),parent);

    connect(return_pressed, SIGNAL(activated()),
            this, SLOT(returnPressedSlot()));

    setFixedHeight(30);
}

MtpEdit::~MtpEdit() {}

void MtpEdit::returnPressedSlot() {
    emit send(toPlainText());
    clear();
}
