/****************************************************************************
** Form implementation generated from reading ui file 'chatpage.ui'
**
** Created: Mon Jan 6 19:27:11 2003
**      by: The User Interface Compiler ($Id: chatpage.cpp,v 1.5 2003/12/28 20:47:59 uid66908 Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

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

   
//     QValueList<int> list = vsplit->sizes();
//     int tmp = list[1];
//     list[1] = 0; // Strange things happend here...
//     list[0] += tmp-list[1];
//     vsplit->setSizes(list);
    
//     list = hsplit->sizes();
//     tmp = list[1];
//     list[1] = 0; // Strange things happend here...
//     list[0] += tmp-list[1];
//     hsplit->setSizes(list);  
    
       ChatPageLayout->addWidget(vsplit,0,0);
       /* 
    ChatPageLayout = new QGridLayout( this, 1, 1, 6, 6, "ChatPageLayout"); 

    chat_edit = new QTextEdit( this, "chat_edit" );
    chat_edit->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, chat_edit->sizePolicy().hasHeightForWidth() ) );
    chat_edit->setMaximumSize( QSize( 32767, 50 ) );
    chat_edit->setFrameShape( QTextEdit::LineEditPanel );

    ChatPageLayout->addMultiCellWidget( chat_edit, 1, 1, 0, 1 );

    users_box = new QListBox( this, "users_box" );
    users_box->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)7, 0, 0, users_box->sizePolicy().hasHeightForWidth() ) );
    users_box->setMaximumSize( QSize( 75, 32767 ) );

    ChatPageLayout->addWidget( users_box, 0, 1 );

    chat_view = new MtpBrowser( this, "chat_view" );

    ChatPageLayout->addWidget( chat_view, 0, 0 );
    languageChange();
    */
    resize( QSize(600, 380).expandedTo(minimumSizeHint()) );
    repaint();
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
    setCaption( tr( "Form1" ) );
    QToolTip::add( chat_edit, tr( "SHIFT+UP/DOWN for history - CTRL+ENTER to insert a new line" ) );
}

void ChatPage::returnPressed()
{
    qWarning( "ChatPage::returnPressed(): Not implemented yet" );
}

