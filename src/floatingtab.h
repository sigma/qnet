/*
 *  File: floatingtab.h
 *  Created: Monday, December 27, 2004
 *  Time-stamp: <28/12/2004 10:15:06 Yann Hodique>
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

#ifndef _FLOATINGTAB_H_
#define _FLOATINGTAB_H_

#include <QTabWidget>

class FloatingTab: public QTabWidget {

    Q_OBJECT

public:
    FloatingTab(QWidget *parent = 0);

    ~FloatingTab();

signals:
    void tabInsertedSignal(int index);
    void tabRemovedSignal(int index);

protected:
    void tabInserted(int index);
    void tabRemoved(int index);

};	// end of class FloatingTab


#endif /* _FLOATINGTAB_H_ */
