/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _PAGE_H_
#define _PAGE_H_

#include <qwidget.h>

#include "master.h"


#define PLUGIN_FACTORY(a,b) \
extern "C" Page* create(QWidget *parent, const char *name, Master *master) {\
    return new a(parent,name,master);\
}\
\
extern "C" void destroy(Page* p) {\
    delete p;\
}\
extern "C" QString name() {\
return b;\
}

/**
 * 
 * Yann Hodique
 **/
class Page : public QWidget {
    Q_OBJECT

public:
    Page(QWidget *parent, const char *name, Master *master, WFlags f = 0) : QWidget(parent,name,f) {
        m_master = master;
    }
    virtual ~Page() {}

    Master * getMaster() {
        return m_master;
    }

    virtual bool isSlave() {return true;}
    virtual void append(const QString &) = 0;
    virtual QString getText() {return QString::null;}
    
public slots:
    virtual void ensureFocus() {}

private:
    Master * m_master;

signals:
    void textDisplayed(QWidget *);
};

typedef Page* create_t(QWidget *, const char *, Master *);
typedef void destroy_t(Page*);
typedef QString name_t();

#endif
