/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _SPLASH_H_
#define _SPLASH_H_

#include "page.h"

class QTimer;
class QLabel;

class Splash : public Page {
    Q_OBJECT

public:
    Splash(QWidget *parent, const char *name, Master * session);
    ~Splash();

    void repaint();
    void setTime(int);
    bool isSlave() {return false;}

protected:
    void mousePressEvent( QMouseEvent * );

public slots:
    void timeout();
    void append(const QString & msg);

private:
    QTimer *m_timer;
    QLabel *m_label;
    int m_screen;
    int time;
};

#endif
