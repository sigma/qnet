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
#include <qtextedit.h>

#include <qvariant.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include <iostream>

#include <qsplitter.h>
#include <qvaluelist.h>

#include "mtpbrowser.h"

PLUGIN_FACTORY(TellPage,"tell");

TellPage::TellPage(QWidget *parent, const char *name, Master * session)
        : Page(parent,name,session) {
    if ( !name )
        setName( "TellPageBase" );
    TellPageBaseLayout = new QGridLayout( this, 1, 1, 11, 6, "TellPageBaseLayout");

    QSplitter *vsplit = new QSplitter(Qt::Vertical,this);
    chat_view = new MtpBrowser( vsplit, "chat_view" );
    chat_edit = new QTextEdit( vsplit, "chat_edit" );
    
    QValueList<int> list = vsplit->sizes();
    int tmp = list[1];
    list[1] = 0; // Strange things happend here...
    list[0] += tmp-list[1];
    vsplit->setSizes(list);

    TellPageBaseLayout->addWidget(vsplit,0,0);
    /*
    chat_edit = new QTextEdit( this, "chat_edit" );
    chat_edit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, chat_edit->sizePolicy().hasHeightForWidth() ) );
    chat_edit->setMaximumSize( QSize( 32767, 50 ) );
    chat_edit->setFrameShape( QTextEdit::LineEditPanel );

    TellPageBaseLayout->addWidget( chat_edit, 1, 0 );

    chat_view = new MtpBrowser( this, "chat_view" );

    TellPageBaseLayout->addWidget( chat_view, 0, 0 );
    languageChange();
    */
    resize( QSize(573, 361).expandedTo(minimumSizeHint()) );

    chat_view->setTextFormat(Qt::RichText);

    chat_view->setWrapPolicy(QTextBrowser::Anywhere);
    chat_view->setLinkUnderline(true);

    QStyleSheetItem *item = new QStyleSheetItem(chat_view->styleSheet(),"mypre");
    item->setWhiteSpaceMode(QStyleSheetItem::WhiteSpacePre);

    history_up = new QAction(chat_edit,"up");
    history_up->setAccel(QKeySequence(SHIFT + Key_Up));
    history_down = new QAction(chat_edit,"down");
    history_down->setAccel(QKeySequence(SHIFT + Key_Down));
    new_line = new QAction(chat_edit,"new");
    new_line->setAccel(QKeySequence(CTRL + Key_Return));

    connect(history_up, SIGNAL(activated()),
            this, SLOT(slotHistoryUp()));
    connect(history_down, SIGNAL(activated()),
            this, SLOT(slotHistoryDown()));
    connect(new_line, SIGNAL(activated()),
            this, SLOT(slotNewLine()));

    connect(chat_edit, SIGNAL(returnPressed()),
            this, SLOT(returnPressed()));
            
    connect(chat_view,SIGNAL(linkClicked(const QString &)),
            session, SLOT(slotLinkClicked(const QString &)));

    chat_edit->setFocus();
    chat_edit->setWordWrap(QTextEdit::NoWrap);
    //chat_edit->setTextFormat(Qt::PlainText);
    
    setPrefix(QString("tell ") + name + " ");
}


TellPage::~TellPage() {}

void TellPage::append(QString &msg) {
    //std::cerr << msg << std::endl;
    chat_view->append(msg);
    emit textDisplayed(this);
}

void TellPage::returnPressed() {
    // delete this $#!@? "\n" we've just inserted
    chat_edit->doKeyboardAction(QTextEdit::ActionBackspace);

    history.push_front(chat_edit->text());

    QString msg(prefix + chat_edit->text());
    this->getMaster()->send(msg);
    chat_edit->clear();

    history_iterator = 0;
}

void TellPage::setPrefix(QString prefix) {
    this->prefix = prefix;
}

void TellPage::languageChange() {
    setCaption( tr( "Tell page" ) );
}

void TellPage::slotHistoryUp() {

    if (history_iterator == 0)
        history_iterator=history.begin();
    else if (history_iterator != (--history.end()))
        history_iterator++;
    chat_edit->setText(*history_iterator);
}

void TellPage::slotHistoryDown() {
    if( history_iterator == 0)
        return;
    if (history_iterator != history.begin()) {
        history_iterator--;
        chat_edit->setText(*history_iterator);
    } else {
        chat_edit->clear();
        history_iterator = 0;
    }
}

void TellPage::slotNewLine() {
    chat_edit->doKeyboardAction(QTextEdit::ActionReturn);
}
