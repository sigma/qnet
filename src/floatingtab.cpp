/*
 *  File: floatingtab.cpp
 *  Created: Monday, December 27, 2004
 *  Time-stamp: <30/12/2004 18:20:37 Yann Hodique>
 *  Copyright: Yann Hodique
 *  Email: Yann.Hodique@lifl.fr
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
    emit tabInsertedSignal(index);
}

void FloatingTab::tabRemoved(int index) {
    emit tabRemovedSignal(index);
}
