/****************************************************************************
** Form interface generated from reading ui file 'chatpage.ui'
**
** Created: Mon Jan 6 19:25:19 2003
**      by: The User Interface Compiler ($Id: chatpage.h,v 1.3 2003/05/06 07:11:36 Sigma Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <qvariant.h>
#include <qwidget.h>

#include <master.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class MtpBrowser;
class QListBox;
class QListBoxItem;
class QTextEdit;

class ChatPage : public Master
{
    Q_OBJECT

public:
    ChatPage( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ChatPage();

    QTextEdit* chat_edit;
    QListBox* users_box;
    MtpBrowser* chat_view;

public slots:
    virtual void returnPressed();

protected:
    QGridLayout* ChatPageLayout;

protected slots:
    virtual void languageChange();
};

#endif // CHATPAGE_H
