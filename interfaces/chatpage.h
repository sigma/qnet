/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <qvariant.h>
#include <qwidget.h>
#include <qstringlist.h>
#include <master.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class MtpBrowser;
class QListBox;
class QListBoxItem;
class QTextEdit;
class QAction;
class QPopupMenu;

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
    void slotHistoryUp();
    void slotHistoryDown();
    void slotNewLine();
    void slotPageUp();
    void slotPageDown();
    void slotHome();
    void slotEnd();
    void removeUser(const QString&);
    void addUser(const QString&);
    void slotContextMenu(QListBoxItem*,const QPoint&);
    void toggleUserMenu(bool);
    void toggleUserBox();

protected:
    QGridLayout* ChatPageLayout;
    QStringList history;
    QStringList::Iterator history_iterator;

protected slots:
    virtual void languageChange();

signals:
	void textDisplayed(QWidget *);
	void outputMessage(const QString& );

private:
    QAction *history_up, *history_down, *new_line, *pgup, *pgdown, *home, *end, *box;
    QPopupMenu *user_menu;
};

#endif // CHATPAGE_H