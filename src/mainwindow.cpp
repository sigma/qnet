/*  Time-stamp: <07/02/2005 21:22:30 Yann Hodique>  */

/**
 *  @file mainwindow.cpp
 *  @date Monday, February 7, 2005
 *  @author Yann Hodique <Yann.Hodique@lifl.fr>
 */

/************************************************************************
 *                                                                      *
 * This program is free software; you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 ************************************************************************/

#include "mainwindow.h"
#include "floatingtab.h"
#include "keymap.h"

#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

#include <iostream>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags, bool transient)
    : QMainWindow(parent, flags) {
    setObjectName("MainWindow");
    setWindowTitle("QNet 2");
    resize(QSize(640,480));

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

void MainWindow::keyPressEvent(QKeyEvent * e) {
    int key = e->key();
    QKeySequence seq(key + e->modifiers());
    KeyMap::ExecutionStatus status = KeyMap::getCurrentKeyMap()->execute(seq);
    switch(status) {
        case KeyMap::Keymap:
            statusBar()->message(seq);
            break;
        case KeyMap::Rejected:
            statusBar()->message("Undefined");
            break;
        case KeyMap::Accepted:
            statusBar()->clear();
            break;
    }
}
