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
        : Page( parent, name, session ), limit(0,0) {
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

    session->context()->setVar("PainterCommands","[EeLlCcTt]");
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

void Painter::append(const QString & str) {
    //std::cerr << s << std::endl;
    QString login,s;
    QRegExp rx("(\\w+) *(\\}.*)");
    if (rx.exactMatch(str)) {
        login = rx.cap(1);
        s = rx.cap(2);

        if (s.startsWith("}L") || s.startsWith("}l")) { // Line
            QRegExp re("\\}[Ll] *(0x)?([0-9A-Fa-f]*) *(\\d+) *(\\d+) *(\\d+) *(\\d+) *(\\d+) *");
            if (re.exactMatch(s)) {
                QColor col(re.cap(2).toUInt(0,16) + 0xff000000);
                QPoint s(re.cap(3).toInt(),re.cap(4).toInt());
                QPoint e(re.cap(5).toInt(),re.cap(6).toInt());
                int w = re.cap(7).toInt();
                canvas->draw(Canvas::LINE,col,s,e,w);
                // TODO : line width
            }
        }
        else if (s.startsWith("}C") || s.startsWith("}c")) { // Circle
            QRegExp re("\\}[Cc] *(0x)?([0-9A-Fa-f]*) *(\\d+) *(\\d+) *(\\d+) *(\\d+) *(\\d+) *");
            if (re.exactMatch(s)) {
                QColor col(re.cap(2).toUInt(0,16) + 0xff000000);
                QPoint s(re.cap(3).toInt(),re.cap(4).toInt());
                QPoint e(re.cap(5).toInt(),re.cap(6).toInt());
                int w = re.cap(7).toInt();
                canvas->draw(Canvas::CIRCLE,col,s,e,w);
            }
        }
        else if (s.startsWith("}T") || s.startsWith("}t")) { // Text
            QRegExp re("\\}[Tt] *(0x)?([0-9A-Fa-f]*) *(\\d+) *(\\d+) *(\\d+) *(\\d+) *([\\w ]+) *");
            if (re.exactMatch(s)) {
                QColor col(re.cap(2).toUInt(0,16) + 0xff000000);
                QPoint s(re.cap(3).toInt(),re.cap(4).toInt());
                QPoint e(re.cap(5).toInt(),re.cap(6).toInt());
                QString text = re.cap(7);
                canvas->draw(Canvas::TEXT,col,s,e,0,text);
            }
        }
        else if (s.startsWith("}E") || s.startsWith("}e")) { // Edge
            QRegExp re("\\}[Ee] *(\\d+) *(\\d+) *");
            if (re.exactMatch(s)) {
                QPoint e(re.cap(1).toInt(),re.cap(2).toInt());
                updateDim(login,e);
            }
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

void Painter::updateDim(const QString& login, const QPoint& point) {
    if(common.find(login) == common.end()) {
        sendOutput(QString("}E %1 %2").arg(canvas->bufferWidth()).arg(canvas->bufferHeight()));
    } else if(common[login] == point) {
        return;
    }

    common[login] = point;
    int x=canvas->bufferWidth(),y=canvas->bufferHeight();
    canvas->draw(Canvas::LINE,colorGroup().base(),QPoint(limit.x(),0),limit,1);
    canvas->draw(Canvas::LINE,colorGroup().base(),limit,QPoint(0,limit.y()),1);
    for(QMap<QString,QPoint>::ConstIterator it = common.begin(); it != common.end(); ++it) {
        if((*it).x() < x)
            x = (*it).x();
        if((*it).y() < y)
            y = (*it).y();
    }
    limit = QPoint(x,y);
    canvas->draw(Canvas::LINE,QColor(0,0,0),QPoint(x,0),QPoint(x,y),1);
    canvas->draw(Canvas::LINE,QColor(0,0,0),QPoint(x,y),QPoint(0,y),1);
    canvas->repaint(true);
}
