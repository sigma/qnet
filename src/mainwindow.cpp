/****************************************************************************
**
** Copyright (C) 1992-2004 Trolltech AS. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "mainwindow.h"
#include "floatingtab.h"

#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

#include <iostream>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags, bool transient)
    : QMainWindow(parent, flags) {
    setObjectName("MainWindow");
    setWindowTitle("QNet 2");
    resize(QSize(600,400));

    this->transient = transient;
    if(!transient) {
        setupMenuBar();
    }
    setupDockWindows();

    statusBar()->message(tr("Status Bar"));
}

void MainWindow::setupMenuBar() {
    QMenu *menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(tr("&Quit"), this, SLOT(close()));
}

void MainWindow::setupDockWindows() {
    ft = new FloatingTab(this);
    setCentralWidget(ft);
    if(transient) {
        connect(ft,SIGNAL(tabRemovedSignal(int)),this,SLOT(checkTabs()));
    }
}

void MainWindow::checkTabs() {
    if(!ft->count())
        deleteLater();
}
