/****************************************************************************
** mainwin.h - the main window.  holds contactlist and buttons.
** Copyright (C) 2001, 2002  Justin Karneges
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,USA.
**
****************************************************************************/

#ifndef MAINWIN_H
#define MAINWIN_H

#include<qdialog.h>
#include<qwidget.h>
#include<qpushbutton.h>
#include<qtoolbutton.h>
#include<qpopupmenu.h>
#include<qlayout.h>
#include<qlabel.h>
#include<qptrvector.h>
#include<qtooltip.h>

#include "trayicon.h"

class MTray : public QObject {
    Q_OBJECT
public:
    MTray(const QImage &icon, const QString &tip, QPopupMenu *popup, QObject *parent=0);
    ~MTray();

    void setToolTip(const QString &);
    void setImage(const QImage &);

signals:
    void clicked(const QPoint &, int);
    void doubleClicked(const QPoint &);
    void closed();

public slots:
    void show();
    void hide();

private:
    TrayIcon *ti;

    QPixmap makeIcon(const QImage &_in);
};

class QMtp;

class MainWin : public QWidget {
    Q_OBJECT
public:
    MainWin(bool onTop, bool asTool, const char *name=0, const QString& rc = QString::null);
    ~MainWin();

    void setUseDock();
    QMtp* qmtp() {
        return mw;
    }
    
signals:
    void closeProgram();

private:

    MTray *tray;
    QMtp* mw;
    QPopupMenu *trayMenu;
    QString icon_path;

  QPoint m_pos;

private slots:
    void buildTrayMenu();

    void trayClicked(const QPoint &, int);
    void trayDoubleClicked();
    void trayShow();
    void trayHide();

    void tryCloseProgram();

};

#endif
