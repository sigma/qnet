/****************************************************************************
** 
** Copyright ( C ) 2002 Yann Hodique <Yann.Hodique@lifl.fr>.
** Copyright ( C ) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <qpen.h>
#include <qpoint.h>
#include <qpixmap.h>
#include <qwidget.h>
#include <qstring.h>
#include <qpointarray.h>

class QMouseEvent;
class QResizeEvent;
class QPaintEvent;
class QToolButton;
class QSpinBox;

class Canvas : public QWidget {
    Q_OBJECT

public:
    typedef enum {
        LINE,
        CIRCLE,
        TEXT
    } Shape;

    Canvas( QWidget *parent = 0, const char *name = 0 );

    void setPenColor( const QColor &c ) {
        pen.setColor( c );
    }

    void setPenWidth( int w ) {
        pen.setWidth( w );
        eraser.setWidth(w);
    }

    void setDrawingShape( Shape s ) {
        shape = s;
    }

    QColor penColor() {
        return pen.color();
    }

    int penWidth() {
        return pen.width();
    }

    int drawingShape() {
        return shape;
    }

    void save( const QString &filename, const QString &format );

    void clearScreen();

protected:
    void mousePressEvent( QMouseEvent *e );
    void mouseReleaseEvent( QMouseEvent *e );
    void mouseMoveEvent( QMouseEvent *e );
    void resizeEvent( QResizeEvent *e );
    void paintEvent( QPaintEvent *e );

    QPen pen,eraser;
    Shape shape;
    QPoint start,tmp;

    bool mousePressed;

    QPixmap buffer,over;

public slots:
    void draw(Shape, const QColor &, const QPoint &, const QPoint &, int width=3, const QString & text = QString::null);

private slots:
    void draw(const QPoint &, const QPoint &, bool definitive=true, bool erase=false);

signals:
    void drawing(const QString & str);
};

#endif
