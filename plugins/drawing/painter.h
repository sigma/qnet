/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *   Copyright (C) 1992-2000 Trolltech AS                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef PAINTER_H
#define PAINTER_H

#include <qvariant.h>
#include <qpixmap.h>

#include "master.h"
#include "page.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class Canvas;
class QComboBox;
class QSpinBox;
class QToolButton;

class Painter : public Page {
    Q_OBJECT

public:
    Painter( QWidget* parent = 0, const char* name = 0, Master * session = 0 );
    ~Painter();

    Canvas* canvas;
    QToolButton* color_button;
    QSpinBox* size_box;
    QComboBox* shape_combo;

public slots:
    void slotColor();
    void slotWidth(int);
    void slotShape(int);
    void append(const QString &);
    void sendOutput(const QString&);

protected:
    QGridLayout* PainterLayout;

protected slots:
    virtual void languageChange();

private:
QString m_prefix;
};

#endif // PAINTER_H
