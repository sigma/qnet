/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include <qapplication.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qcolor.h>

#include "splash.h"

PLUGIN_FACTORY(Splash,"splash");

Splash::Splash(QWidget * /*parent*/, const char *name, Master * session) 
    : Page(0, name, session, WStyle_Customize | WStyle_Splash), label(this) {
    QColor color1("lightgrey");
//    QColor color2("white");
    label.setPaletteBackgroundColor(color1);
    m_timer = new QTimer(this);
    time = 2000;
}

Splash::~Splash() {}

void Splash::repaint() {
    QWidget::repaint();
    QApplication::flush();
}

void Splash::setTime(int ms) {
    time = ms;
}

void Splash::mousePressEvent( QMouseEvent * ) {
    hide();
}

void Splash::timeout() {
    hide();
}

void Splash::append(QString & msg) {
    
    m_timer->stop();
    label.setText(msg);
    label.adjustSize();
    resize(label.size());
    QRect scr = QApplication::desktop()->screenGeometry();
    
    move( scr.bottomRight() - rect().center() - rect().center());
    show();
    repaint();
    
    m_timer = new QTimer();
    
    connect(m_timer, SIGNAL(timeout()),
	    SLOT(timeout()));
    
    m_timer->start(time,true);
    
}
