/*
 *  File: floatingtab.h
 *  Created: Monday, December 27, 2004
 *  Time-stamp: <21/01/2005 16:30:53 Yann Hodique>
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

/**
 * A simple wrapper around QTabWidget for using a QTabBar
 *
 */
class FloatingTab: public QTabWidget {

    Q_OBJECT

public:
    /**
     * Constructor
     *
     * @param parent the parent QWidget
     *
     */
    FloatingTab(QWidget *parent = 0);

    /**
     * Destructor
     *
     */
    ~FloatingTab();

signals:
    /**
     * signal emitted whenever a QWidget is inserted into the QTabWidget
     *
     * @param index the index of the inserted QWidget
     */
    void tabInsertedSignal(int index);

    /**
     * signal emitted whenever a QWidget is removed from the QTabWidget
     *
     * @param index the index of the removed QWidget
     */
    void tabRemovedSignal(int index);

protected:
    /**
     * action performed when a QWidget is inserted
     *
     * @param index the index of the inserted QWidget
     */
    void tabInserted(int index);

    /**
     * action performed when a QWidget is removed
     *
     * @param index the index of the removed QWidget
     */
    void tabRemoved(int index);

};	// end of class FloatingTab


#endif /* _FLOATINGTAB_H_ */
