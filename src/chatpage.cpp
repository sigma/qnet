/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "chatpage.h"

#include <qvariant.h>
#include <qlistbox.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include <qsplitter.h>
#include <qvaluelist.h>
#include <qaction.h>

#include "mtpbrowser.h"

/* 
 *  Constructs a ChatPage as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ChatPage::ChatPage( QWidget* parent, const char* name, WFlags fl )
    : Master( parent, name, fl )
{
    if ( !name )
	setName( "ChatPage" );
        
    ChatPageLayout = new QGridLayout( this, 1, 1, 6, 6, "ChatPageLayout");
    
    QSplitter *vsplit = new QSplitter(Qt::Vertical,this);
    QSplitter *hsplit = new QSplitter(Qt::Horizontal,vsplit);
  
 
    chat_view = new MtpBrowser(hsplit,"chat_view");
    chat_view->setMinimumSize( QSize( 525, 330 ) );
    users_box = new QListBox(hsplit,"users_box");

    users_box->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)7, 0, 0, users_box->sizePolicy().hasHeightForWidth() ) );
    users_box->setMinimumSize( QSize( 75, 330 ) );

    chat_edit = new QTextEdit(vsplit,"chat_edit");

    chat_edit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, chat_edit->sizePolicy().hasHeightForWidth() ) );
    chat_edit->setMinimumSize( QSize( 600, 50 ) );
    chat_edit->setFrameShape( QTextEdit::LineEditPanel );

    ChatPageLayout->addWidget(vsplit,0,0);

    resize( QSize(600, 380).expandedTo(minimumSizeHint()) );
    repaint();

    chat_view->setTextFormat(Qt::RichText);

    chat_view->setWrapPolicy(QTextBrowser::Anywhere);
    chat_view->setLinkUnderline(true);

    history_up = new QAction(chat_edit,"up");
    history_up->setAccel(QKeySequence(SHIFT + Key_Up));
    history_down = new QAction(chat_edit,"down");
    history_down->setAccel(QKeySequence(SHIFT + Key_Down));
    new_line = new QAction(chat_edit,"new");
    new_line->setAccel(QKeySequence(CTRL + Key_Return));

    pgup = new QAction(chat_edit,"pgup");
    pgup->setAccel(QKeySequence(Key_PageUp));
    pgdown = new QAction(chat_edit,"pgdown");
    pgdown->setAccel(QKeySequence(Key_PageDown));

    connect(history_up, SIGNAL(activated()),
            this, SLOT(slotHistoryUp()));
    connect(history_down, SIGNAL(activated()),
            this, SLOT(slotHistoryDown()));
    connect(new_line, SIGNAL(activated()),
            this, SLOT(slotNewLine()));

    connect(chat_view,SIGNAL(linkClicked(const QString &)),
            this, SLOT(slotLinkClicked(const QString &)));

    connect(chat_edit, SIGNAL(returnPressed()),
            this, SLOT(returnPressed()));

    connect(pgup,SIGNAL(activated()),
            this,SLOT(slotPageUp()));
    connect(pgdown,SIGNAL(activated()),
            this,SLOT(slotPageDown()));

//     connect(users_box, SIGNAL(doubleClicked(QListBoxItem*)),
//             this,SLOT(slotUserDoubleClicked(QListBoxItem*)));
    
    chat_edit->setFocus();
    chat_edit->setWordWrap(QTextEdit::NoWrap);
    chat_edit->setTextFormat(Qt::PlainText);

    history_iterator = 0;

    setFocusProxy(chat_edit);
}

/*
 *  Destroys the object and frees any allocated resources
 */
ChatPage::~ChatPage()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ChatPage::languageChange()
{
    setCaption( tr( "ChatPage" ) );
    QToolTip::add( chat_edit, tr( "SHIFT+UP/DOWN for history - CTRL+ENTER to insert a new line" ) );
}

void ChatPage::returnPressed()
{
    qWarning( "ChatPage::returnPressed(): Not implemented yet" );
}

void ChatPage::ensureFocus() {
    chat_edit->setFocus();
}

void ChatPage::slotHistoryUp() {

    if (history_iterator == 0)
        history_iterator=history.begin();
    else if (history_iterator != (--history.end()))
        history_iterator++;
    chat_edit->setText(*history_iterator);
}

void ChatPage::slotHistoryDown() {
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

void ChatPage::slotNewLine() {
    chat_edit->doKeyboardAction(QTextEdit::ActionReturn);
}

void ChatPage::slotPageUp() {
    chat_view->moveCursor(QTextEdit::MovePgUp,false);
}

void ChatPage::slotPageDown() {
    chat_view->moveCursor(QTextEdit::MovePgDown,false);
}

void ChatPage::addUser(const QString& name) {
    users_box->insertItem(name);
    users_box->sort();
}

void ChatPage::removeUser(const QString& name) {
    QListBoxItem * item = users_box->findItem(name,Qt::ExactMatch);
    delete item;
}

