/*  Time-stamp: <07/02/2005 21:21:57 Yann Hodique>  */

/**
 *  @file floatingtab.cpp
 *  @date Monday, December 27, 2004
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

#include "floatingtab.h"
#include "floatingtabbar.h"

FloatingTab::FloatingTab(QWidget *parent) : QTabWidget(parent) {
    setTabBar(new FloatingTabBar(this));
}

FloatingTab::~FloatingTab() {}

void FloatingTab::tabInserted(int index) {
    if(count() == 1)
        setTabEnabled(index,true);
    widget(index)->setFocus();
    emit tabInsertedSignal(index);
}

void FloatingTab::tabRemoved(int index) {
    emit tabRemovedSignal(index);
}
