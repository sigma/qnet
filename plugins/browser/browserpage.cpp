/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "browserpage.h"
#include "mtpbrowser.h"

#include <qlayout.h>

PLUGIN_FACTORY(BrowserPage,"browser");

BrowserPage::BrowserPage(QWidget *parent, const char *name, Master * session)
        : Page(parent,name,session) {
    if ( !name )
        setName( "BrowserPageBase" );
    BrowserPageBaseLayout = new QGridLayout( this, 1, 1, 6, 6, "TellPageBaseLayout");

    chat_view = new MtpBrowser( this, "chat_view" );

    BrowserPageBaseLayout->addWidget( chat_view, 0, 0 );
    languageChange();
    resize( QSize(600, 380).expandedTo(minimumSizeHint()) );

    chat_view->setTextFormat(Qt::RichText);
    chat_view->setSizePolicy( QSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding, 0, 0, chat_view->sizePolicy().hasHeightForWidth() ) );
    chat_view->setWrapPolicy(QTextBrowser::Anywhere);
    chat_view->setLinkUnderline(true);

    QStyleSheetItem *item = new QStyleSheetItem(chat_view->styleSheet(),"mypre");
    item->setWhiteSpaceMode(QStyleSheetItem::WhiteSpacePre);

    connect(chat_view,SIGNAL(linkClicked(const QString &)),
            session, SLOT(slotLinkClicked(const QString &)));
}


BrowserPage::~BrowserPage() {}

void BrowserPage::append(const QString &msg) {
    //std::cerr << msg << std::endl;
    chat_view->append(msg);
    emit textDisplayed(this);
}

void BrowserPage::languageChange() {
    setCaption( tr( "Tell page" ) );
}

QString BrowserPage::getText() {
    return chat_view->text();
}
