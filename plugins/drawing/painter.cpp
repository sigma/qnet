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

#include "painter.h"
#include "canvas.h"

#include <iostream>
#include <qvariant.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qcolordialog.h>
#include <qregexp.h>

PLUGIN_FACTORY(Painter,"drawing");
/*
 *  Constructs a Painter as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
Painter::Painter( QWidget* parent, const char* name, Master * session )
        : Page( parent, name, session ) {
    if ( !name )
        setName( "Painter" );
    PainterLayout = new QGridLayout( this, 1, 1, 6, 6, "PainterLayout");

    canvas = new Canvas( this, "myCustomWidget1" );

    PainterLayout->addMultiCellWidget( canvas, 1, 1, 0, 3 );
    QSpacerItem* spacer = new QSpacerItem( 330, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    PainterLayout->addItem( spacer, 0, 3 );

    color_button = new QToolButton( this, "color_button" );
    connect(color_button, SIGNAL(pressed()), this, SLOT(slotColor()));

    PainterLayout->addWidget( color_button, 0, 0 );

    size_box = new QSpinBox( this, "size_box" );
    size_box->setMaxValue( 20 );
    size_box->setMinValue( 1 );
    size_box->setValue( 3 );

    PainterLayout->addWidget( size_box, 0, 1 );

    shape_combo = new QComboBox( FALSE, this, "shape_combo" );
    connect(shape_combo, SIGNAL(activated(int)), this, SLOT(slotShape(int)));

    PainterLayout->addWidget( shape_combo, 0, 2 );
    languageChange();
    resize( QSize(548, 426).expandedTo(minimumSizeHint()) );

    connect( size_box, SIGNAL( valueChanged( int ) ), this, SLOT( slotWidth( int ) ) );

    connect(canvas,SIGNAL(drawing(const QString&)),SLOT(sendOutput(const QString&)));

    QRegExp re("\\w+@(\\w+)");
    if (re.exactMatch(name))
        m_prefix="senddata " + re.cap(1) + " ";
    else
        m_prefix=QString::null;
}

/*
 *  Destroys the object and frees any allocated resources
 */
Painter::~Painter() {
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Painter::languageChange() {
    setCaption( tr( "Form1" ) );
    color_button->setText( tr( "Color" ) );
    shape_combo->clear();
    shape_combo->insertItem( tr( "Line" ) );
    shape_combo->insertItem( tr( "Circle" ) );
    shape_combo->insertItem( tr( "Text" ) );
}

void Painter::slotColor() {
    QColor c = QColorDialog::getColor( canvas->penColor(), this );
    if ( c.isValid() )
        canvas->setPenColor( c );
}

void Painter::slotWidth( int w ) {
    canvas->setPenWidth( w );
}

void Painter::slotShape(int s) {
    canvas->setDrawingShape((Canvas::Shape)s);
}

void Painter::append(const QString & s) {
    //std::cerr << s << std::endl;
    if (s.startsWith("}L")) { // Line
        QRegExp re("\\}L *0x([0-9A-Fa-f]*) *(\\d+) *(\\d+) *(\\d+) *(\\d+) *(\\d+) *");
        if (re.exactMatch(s)) {
            QColor col(re.cap(1).toUInt(0,16) + 0xff000000);
            QPoint s(re.cap(2).toInt(),re.cap(3).toInt());
            QPoint e(re.cap(4).toInt(),re.cap(5).toInt());
            int w = re.cap(6).toInt();
            canvas->draw(Canvas::LINE,col,s,e,w);
            // TODO : line width
        }
    }
    else if (s.startsWith("}C")) { // Circle
        QRegExp re("\\}C *0x([0-9A-Fa-f]*) *(\\d+) *(\\d+) *(\\d+) *(\\d+) *");
        if (re.exactMatch(s)) {
            QColor col(re.cap(1).toUInt(0,16) + 0xff000000);
            QPoint s(re.cap(2).toInt(),re.cap(3).toInt());
            QPoint e(re.cap(2).toInt(),re.cap(3).toInt()+re.cap(4).toInt());
            int w = re.cap(5).toInt();
            canvas->draw(Canvas::CIRCLE,col,s,e,w);
        }
    }
    else if (s.startsWith("}T")) { // Text
        QRegExp re("\\}T *0x([0-9A-Fa-f]*) *(\\d+) *(\\d+) *([\\w ]+) *([\\w ]+) *");
        if (re.exactMatch(s)) {
            QColor col(re.cap(1).toUInt(0,16) + 0xff000000);
            QPoint s(re.cap(2).toInt(),re.cap(3).toInt());
            QString text = re.cap(6);
            canvas->draw(Canvas::TEXT,col,s,s,0,text);
        }
    }
}

void Painter::sendOutput(const QString& msg) {
  if (!m_prefix.isNull())
      getMaster()->send(m_prefix + msg);
  else if(getMaster()->context()->getValue("channel") == "Dessin")
      getMaster()->send(msg);
  else
      getMaster()->displayStderr("not in Dessin channel");
}
