/*
 *  File: floatingtabbar.h
 *  Created: Monday, December 27, 2004
 *  Time-stamp: <21/01/2005 16:33:34 Yann Hodique>
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

#ifndef _FLOATINGTABBAR_H_
#define _FLOATINGTABBAR_H_

#include <QTabBar>

class QRubberBand;
class QPoint;
class QRect;
class FloatingTab;

/**
 * Floating QTabBar. It can be dragged by pressing mouse-2 button
 *
 * @todo allow customization of the bindings
 *
 */
class FloatingTabBar: public QTabBar {

    Q_OBJECT

public:
    /**
     * Constructor
     *
     * @param parent the parent QWidget
     *
     */
    FloatingTabBar(QWidget *parent = 0);

    /**
     * Destructor
     *
     */
    ~FloatingTabBar();

protected:
    /**
     * Re-implementation of parent's event handler
     *
     * @param event received event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * Re-implementation of parent's event handler
     *
     * @param event received event
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * Re-implementation of parent's event handler
     *
     * @param event received event
     */
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int indexByPoint(const QPoint&);

    struct DragState {
        QWidget *widget;
        QRubberBand *rubberband;
        QRect origin;   // starting position
        QRect current;  // current size of the dockwindow (can be either placed or floating)
    };
    DragState *state;

    FloatingTab *tab;
};	// end of class FloatingTabBar


#endif /* _FLOATINGTABBAR_H_ */
