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
#include <qregexp.h>
#include <qpoint.h>
#include <qcursor.h>

#include "splash.h"

#define Style_Splash WStyle_NoBorder | WStyle_StaysOnTop | WStyle_Tool | WX11BypassWM | WWinOwnDC

PLUGIN_FACTORY(Splash,"splash");

Splash::Splash(QWidget * /*parent*/, const char *name, Master * session) 
    : Page(0, name, session, WStyle_Customize | Style_Splash) {
    m_screen = QApplication::desktop()->primaryScreen();
    
    m_label = new QLabel(this);
    m_label->setPaletteBackgroundColor(QColor("lightgrey"));

    setFocusPolicy(QWidget::NoFocus);
    m_timer = new QTimer(this);
    time = 3000;

    connect(m_timer, SIGNAL(timeout()),
            SLOT(timeout()));

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

void Splash::append(const QString & msg) {

    QRegExp re("\\[([NS]?)([EO]?)\\](.*)");
    if(re.exactMatch(msg)) {
        m_timer->stop();
        m_label->setText(re.cap(3).replace(QRegExp("&gt "),">").replace(QRegExp("&lt "),"<").replace(QRegExp("&amp "),"&"));
        m_label->adjustSize();
        resize(m_label->size());

        QRect scr = QApplication::desktop()->screenGeometry(QCursor::pos());

        QPoint pt = scr.center();

        if(re.cap(1) == "S") {
            pt.setY(scr.height() - rect().height());
        } else if(re.cap(1) == "N") {
            pt.setY(0);
        } else {
            pt.setY(pt.y() - rect().height()/2);
        }
        
        if(re.cap(2) == "E") {
            pt.setX(scr.width() - rect().width());
        } else if(re.cap(2) == "O") {
            pt.setX(0);
        } else {
            pt.setX(pt.x() - rect().width()/2);
        }
        
        move(pt);
        show();
        repaint();
    
        m_timer->start(time,true);
    }
}
