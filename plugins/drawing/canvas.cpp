/****************************************************************************
**
** Copyright ( C ) 2002 Yann Hodique <Yann.Hodique@lifl.fr>.
** Copyright ( C ) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#include "canvas.h"

#include <math.h>
#include <iostream>
#include <qinputdialog.h>
#include <qevent.h>
#include <qpainter.h>
#include <qtooltip.h>
#include <qrect.h>
#include <qpoint.h>
#include <qcolordialog.h>
#include <qfiledialog.h>
#include <qcursor.h>
#include <qimage.h>
#include <qstrlist.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)<(b))?(b):(a))
#define abs(a) (((a)<0)?(-(a)):(a))

const bool no_writing = FALSE;

Canvas::Canvas( QWidget *parent, const char *name )
        : QWidget( parent, name, WStaticContents ), pen( Qt::red, 3 ), eraser(colorGroup().base(),3),
mousePressed( FALSE ), buffer( width(), height() ) {
    setBackgroundMode( QWidget::PaletteBase );
#ifndef QT_NO_CURSOR

    setCursor( Qt::crossCursor );
#endif

    clearScreen();
    shape = LINE;
}

void Canvas::save( const QString &filename, const QString &format ) {
    if ( !no_writing )
        buffer.save( filename, format.upper() );
}

void Canvas::clearScreen() {
    buffer.fill( colorGroup().base() );
    repaint( FALSE );
}

void Canvas::mousePressEvent( QMouseEvent *e ) {
    mousePressed = TRUE;
    start = e->pos();
}

void Canvas::mouseReleaseEvent( QMouseEvent *e ) {
    mousePressed = FALSE;
    draw(start,e->pos());
    repaint(true);
}

void Canvas::draw(const QPoint & q, const QPoint & p, bool definitive, bool erase) {
    QPainter painter;
    if (definitive)
        painter.begin( &buffer );
    else {
        over = buffer;
        painter.begin(&over);
    }
    painter.setPen( erase?eraser:pen );

    QPointArray parray(2);
    QString description;

    switch (shape) {
    case LINE:
        if(definitive)
	    description = QString("}L 0x%1 %2 %3 %4 %5 %6").arg(penColor().rgb()-0xff000000,0,16)
                          .arg(q.x()).arg(q.y()).arg(p.x()).arg(p.y()).arg(penWidth());
        painter.drawLine(q,p);
        parray[1] = q;
        parray[0] = p;
        break;
    case CIRCLE:
    {
            painter.drawEllipse(QRect(p,q));
            parray[1] = q;
            parray[0] = p;
            if(definitive)
                description = QString("}C 0x%1 %2 %3 %4 %5 %6")
                    .arg(penColor().rgb()-0xff000000,0,16)
                    .arg(q.x()).arg(q.y())
                    .arg(p.x()).arg(p.y())
                    .arg(penWidth());

    }
    break;
    case TEXT:
        if(definitive) {
            QString text = QInputDialog::getText("Text Input","Enter text");
            painter.drawText(min(q.x(),p.x()),min(q.y(),p.y()),abs(q.x()-p.x()),abs(q.y()-p.y()),
                             Qt::AlignAuto|Qt::AlignVCenter|Qt::BreakAnywhere,text);
            description = QString("}T 0x%1 %2 %3 %4 %5 %6").arg(penColor().rgb()-0xff000000,0,16)
                .arg(min(q.x(),p.x())).arg(min(q.y(),p.y()))
                .arg(max(q.x(),p.x())).arg(max(q.y(),p.y()))
                .arg(text);
        }
        else {
            painter.drawRect(min(q.x(),p.x()),min(q.y(),p.y()),abs(q.x()-p.x()),abs(q.y()-p.y()));
        }
        parray[1] = q;
        parray[0] = p;
        break;
    }

    painter.end();

    QRect r = parray.boundingRect();
    r = r.normalize();
    r.setLeft( r.left() - penWidth() );
    r.setTop( r.top() - penWidth() );
    r.setRight( r.right() + penWidth() );
    r.setBottom( r.bottom() + penWidth() );

    bitBlt( this, r.x(), r.y(), definitive?(&buffer):(&over), r.x(), r.y(), r.width(), r.height() );
    if(definitive) {
        emit drawing(description);
    }
}

void Canvas::draw(Shape s, const QColor & col, const QPoint & q, const QPoint & p, int width, const QString & text) {

    if (max(q.x(),p.x()) > buffer.width() || max(q.y(),p.y()) > buffer.height()) {
	QPixmap tmp( buffer );
	buffer.resize(max(q.x(),p.x()),max(q.y(),p.y()));
	buffer.fill( colorGroup().base() );
	bitBlt( &buffer, 0, 0, &tmp, 0, 0, tmp.width(), tmp.height() );
    }

    QPainter painter;
    painter.begin( &buffer );
    QPen mpen(col,width);
    painter.setPen(mpen);


    QPointArray parray(2);

    switch (s) {
    case LINE:
        painter.drawLine(q,p);
        parray[1] = q;
        parray[0] = p;
        break;
    case CIRCLE:
        {
            painter.drawEllipse(QRect(p,q));
            parray[1] = p;
            parray[0] = q;
        }
        break;
    case TEXT:
        painter.drawText(min(q.x(),p.x()),min(q.y(),p.y()),abs(q.x()-p.x()),abs(q.y()-p.y()),
                         Qt::AlignAuto|Qt::AlignVCenter|Qt::BreakAnywhere,text);
        parray[1] = q;
        parray[0] = p;
        break;
    }

    painter.end();

    QRect r = parray.boundingRect();
    r = r.normalize();
    r.setLeft( r.left() - width );
    r.setTop( r.top() - width );
    r.setRight( r.right() + width );
    r.setBottom( r.bottom() + width );

    bitBlt( this, r.x(), r.y(),&buffer, r.x(), r.y(), r.width(), r.height() );
}

void Canvas::mouseMoveEvent( QMouseEvent *e ) {
    if(mousePressed) {
        draw(start,tmp,false,true);
        draw(start,e->pos(),false);
        tmp=e->pos();
    }
}

void Canvas::resizeEvent( QResizeEvent *e ) {
    QWidget::resizeEvent( e );

    int w = width() > buffer.width() ?
            width() : buffer.width();
    int h = height() > buffer.height() ?
            height() : buffer.height();

    QPixmap tmp( buffer );
    buffer.resize( w, h );
    buffer.fill( colorGroup().base() );
    bitBlt( &buffer, 0, 0, &tmp, 0, 0, tmp.width(), tmp.height() );

    QString description = QString("}E %1 %2").arg(buffer.width()).arg(buffer.height());
    emit drawing(description);
}

void Canvas::paintEvent( QPaintEvent *e ) {
    QWidget::paintEvent( e );

    QMemArray<QRect> rects = e->region().rects();
    for ( uint i = 0; i < rects.count(); i++ ) {
        QRect r = rects[(int)i];
        bitBlt( this, r.x(), r.y(), &buffer, r.x(), r.y(), r.width(), r.height() );
    }
}
