/*  Time-stamp: <08/02/2005 09:41:56 Yann Hodique>  */

/**
 *  @file mtparea.cpp
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

#include "mtparea.h"
#include "mtpedit.h"
#include "mtpinfo.h"

#include <QBoxLayout>
#include <QSplitter>
#include <QAction>

#include <iostream>

MtpArea::MtpArea(QWidget *parent) : InteractionArea(parent), QWidget(parent) {
    chatpage_layout = new QBoxLayout(QBoxLayout::LeftToRight, this);

    vsplit = new QSplitter(Qt::Vertical,this);

    hsplit = new QSplitter(Qt::Horizontal,vsplit);

    chat_view = new MtpBrowser(hsplit);
    users_box = new MtpInfo(hsplit);

    chat_edit = new MtpEdit(vsplit);

    chatpage_layout->addWidget(vsplit);


    repaint();

     ((InteractionArea*)this)->connect(chat_edit, SIGNAL(send(const QString&)),
                                       (InteractionArea*)this, SIGNAL(send(const QString&)));

    chat_edit->setFocus();

    chat_view->setFocusProxy(chat_edit);
    users_box->setFocusProxy(chat_edit);
    this->setFocusProxy(chat_edit);

    users_box->resize(50,users_box->size().height());
}

MtpArea::~MtpArea() {
}

MtpOutput * MtpArea::getOutput() const {
    return chat_view;
}

MtpInput * MtpArea::getInput()  const {
    return chat_edit;
}

void MtpArea::returnPressed() {
    slotSend(chat_edit->toPlainText());
    chat_edit->clear();
}

void MtpArea::toggleUserBox() {
    if(user_box_visible) {
        user_box_visible = false;
        users_box->hide();
    }
    else {
        users_box->show();
        user_box_visible = true;
    }
}

void MtpArea::resizeEvent ( QResizeEvent * // e
                            ) {
//    QWidget::resizeEvent(e);
}
