/*  Time-stamp: <08/02/2005 09:23:30 Yann Hodique>  */

/**
 *  @file mainwindow.h
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

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>

class ToolBar;
class QMenu;
class FloatingTab;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0, bool transient = true);
    FloatingTab* getFloatingTab() const {return ft;}
    ToolBar* getToolBar() const {return toolbar;}

protected:
   void MainWindow::keyPressEvent(QKeyEvent *);

private:
    void setupToolBar();
    void setupMenuBar();
    void setupDockWindows();

    bool transient;
    FloatingTab *ft;
    ToolBar *toolbar;
    QMenu *dockWindowMenu;

private slots:
    void checkTabs();
};

#endif /* _MAINWINDOW_H_ */
