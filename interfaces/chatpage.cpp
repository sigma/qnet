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
#include <qpopupmenu.h>
#include <qsplitter.h>
#include <qvaluelist.h>
#include <qaction.h>
#include <qpoint.h>

#include "mtpbrowser.h"

#define DEFAULT_BOOKMARK "[Mark]"

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
    chat_view->setSizePolicy(QSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored, 0, 0, chat_view->sizePolicy().hasHeightForWidth() ));
    users_box = new QListBox(hsplit,"users_box");

    hsplit->setResizeMode(users_box,QSplitter::KeepSize);

    users_box->setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::MinimumExpanding, 0, 0, users_box->sizePolicy().hasHeightForWidth() ) );
    users_box->setMinimumSize( QSize( 75, 330 ) );

    chat_edit = new QTextEdit(vsplit,"chat_edit");

    vsplit->setResizeMode(chat_edit,QSplitter::KeepSize);

    chat_edit->setSizePolicy( QSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Fixed, 0, 0, chat_edit->sizePolicy().hasHeightForWidth() ) );
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

    pgup = new QAction(this,"pgup");
    pgup->setAccel(QKeySequence(ALT + Key_PageUp));
    pgdown = new QAction(this,"pgdown");
    pgdown->setAccel(QKeySequence(ALT + Key_PageDown));
    home = new QAction(this,"home");
    home->setAccel(QKeySequence(ALT + Key_Home));
    end = new QAction(this,"end");
    end->setAccel(QKeySequence(ALT + Key_End));

    box = new QAction(this,"box");
    box->setAccel(QKeySequence(CTRL + Key_H));
    bookmark = new QAction(this,"bookmark");
    bookmark->setAccel(QKeySequence(CTRL + Key_Space));
    gotob = new QAction(this,"goto");
    gotob->setAccel(QKeySequence(CTRL + Key_J));

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
    connect(home,SIGNAL(activated()),
            this,SLOT(slotHome()));
    connect(end,SIGNAL(activated()),
            this,SLOT(slotEnd()));

    connect(box,SIGNAL(activated()),
            this,SLOT(toggleUserBox()));
    connect(bookmark,SIGNAL(activated()),
            this,SLOT(slotBookmark()));
    connect(gotob,SIGNAL(activated()),
            this,SLOT(slotGoto()));

//     connect(users_box, SIGNAL(doubleClicked(QListBoxItem*)),
//             this,SLOT(slotUserDoubleClicked(QListBoxItem*)));

    chat_edit->setFocus();
    chat_edit->setWordWrap(QTextEdit::NoWrap);
    chat_edit->setTextFormat(Qt::PlainText);

    history_iterator = 0;

    chat_view->setFocusProxy(chat_edit);
    users_box->setFocusProxy(chat_edit);

    user_menu = new QPopupMenu(users_box);
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

void ChatPage::slotHome() {
    chat_view->moveCursor(QTextEdit::MoveHome,false);
}

void ChatPage::slotEnd() {
    chat_view->moveCursor(QTextEdit::MoveEnd,false);
}

void ChatPage::slotBookmark() {
    chat_view->slotBookmark(DEFAULT_BOOKMARK);
}

void ChatPage::slotGoto() {
    chat_view->slotGoto(DEFAULT_BOOKMARK);
}

void ChatPage::addUser(const QString& name) {
    users_box->insertItem(name);
    users_box->sort();
}

void ChatPage::removeUser(const QString& name) {
    QListBoxItem * item = users_box->findItem(name,Qt::ExactMatch);
    delete item;
}

void ChatPage::slotContextMenu(QListBoxItem*,const QPoint& pos) {
    user_menu->popup(pos);
}

void ChatPage::toggleUserMenu(bool on) {
    if(on) {
        users_box->setSelectionMode(QListBox::Extended);
        connect(users_box, SIGNAL(contextMenuRequested(QListBoxItem*,const QPoint&)),
                this,SLOT(slotContextMenu(QListBoxItem*,const QPoint&)));
    }
    else {
        users_box->setSelectionMode(QListBox::NoSelection);
        disconnect(users_box, SIGNAL(contextMenuRequested(QListBoxItem*,const QPoint&)),
                this,SLOT(slotContextMenu(QListBoxItem*,const QPoint&)));
    }
}

void ChatPage::toggleUserBox() {
    if(users_box->isVisible())
        users_box->hide();
    else
        users_box->show();
}
