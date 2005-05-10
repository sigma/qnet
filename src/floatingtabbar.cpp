/*  Time-stamp: <09/05/2005 17:37:03 Yann Hodique>  */

/**
 *  @file floatingtabbar.cpp
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

#include "floatingtabbar.h"
#include "floatingtab.h"
#include "mainwindow.h"

#include <QMouseEvent>
#include <QApplication>
#include <QRubberBand>
#include <QDesktopWidget>

#include <iostream>

FloatingTabBar::FloatingTabBar(QWidget *parent) : QTabBar(parent), state(0) {
    tab = qobject_cast<FloatingTab*>(parent);
}

FloatingTabBar::~FloatingTabBar() {}

void FloatingTabBar::mousePressEvent(QMouseEvent *event) {
    if (event->button() != Qt::MidButton) {
        QTabBar::mousePressEvent(event);
        return;
    }

    Q_ASSERT(!state);

    int index = indexByPoint(event->pos());
    if(index == -1) return;

    state = new DragState;

    const int screen_number = QApplication::desktop()->screenNumber(topLevelWidget());
    state->rubberband = new QRubberBand(QRubberBand::Rectangle,
                                        QApplication::desktop()->screen(screen_number));

    state->widget = tab->widget(index);
    // the current location of the tool window in global coordinates
    QRect r = tabRect(index);
    state->origin = QRect(mapToGlobal(r.topLeft()),r.size());
    state->current = state->origin;

    state->rubberband->setGeometry(state->current);
    state->rubberband->show();
}

void FloatingTabBar::mouseMoveEvent(QMouseEvent *event) {
    if (!state) return;

    QRect target;
    target = state->current;
    target.moveCenter(event->globalPos());

    if (state->current == target) return;

    state->rubberband->setGeometry(target);
    state->current = target;
}

void FloatingTabBar::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() != Qt::MidButton) {
        QTabBar::mouseReleaseEvent(event);
        return;
    }

    if (!state) return;

    delete state->rubberband;

    QWidget *focus = qApp->focusWidget();

    QWidget *widget = QApplication::widgetAt(event->globalPos());
    while (widget && !qobject_cast<FloatingTab *>(widget)) {
        if (widget->isTopLevel()) {
            widget = 0;
            break;
        }
        widget = widget->parentWidget();
    }

    FloatingTab *ft;
    if (widget) {
        ft = qobject_cast<FloatingTab *>(widget);
    } else {
        MainWindow *mw = new MainWindow;
        mw->show();
        ft = qobject_cast<FloatingTab*>(mw->centralWidget());
    }
    if (ft && (ft != tab)) {
        int index = tab->indexOf(state->widget);
        QString title = tab->tabText(index);
        tab->removeTab(index);
        ft->addTab(state->widget,title);
    }

    // restore focus
    if (focus) focus->setFocus();

    delete state;
    state = 0;
}

int FloatingTabBar::indexByPoint(const QPoint& p) {
    for(int i = 0; i<count(); i++) {
        QRect r = tabRect(i);
        if(r.contains(p))
            return i;
    }
    return -1;
}
