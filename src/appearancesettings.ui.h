/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <qlistbox.h>

#include "mtpbrowser.h"

void AppearanceSettings::init() {
    ChatPage * cp;
    cp = new ChatPage;

    tabs->insertTab(cp,"@session");

    browser->setText("Here will come various messages, maybe debug ones");
    edit->setText("Lisp interaction area");
    edit->setReadOnly(true);
    cp->chat_view->setText("No remembered size for this part.\nThe height of input and the width of sidebar will be remembered, and remain fixed when you resize the window.");
    cp->chat_edit->setText("Input");
    cp->chat_edit->setReadOnly(true);
    cp->users_box->insertItem("sidebar");
}

void AppearanceSettings::slotTabPosition(int pos)
{
//    tabWidgetTest->setTabPosition(b?QTabWidget::Top : QTabWidget::Bottom);
    switch(pos) {
    case QButton::On :
	tabs->setTabPosition(QTabWidget::Top);
	break;
    default :
	tabs->setTabPosition(QTabWidget::Bottom);
    }
}
