/*
 *  File: floatingtabbar.h
 *  Created: Monday, December 27, 2004
 *  Time-stamp: <28/12/2004 09:39:49 Yann Hodique>
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

class FloatingTabBar: public QTabBar {

    Q_OBJECT

public:
    FloatingTabBar(QWidget *parent = 0);
    ~FloatingTabBar();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
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
