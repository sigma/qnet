 /**************************************************************************
 *  file                 : mtpbrowser.cpp                                  *
 *  begin                : Tuesday, December 30, 2003                      *
 *                           -------------------                           *
 *  copyright            : Yann Hodique                                    *
 *  email                : Yann.Hodique@lifl.fr                            *
 **************************************************************************/

 /**************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 **************************************************************************/

#include "mtpbrowser.h"
#include <qpopupmenu.h>
#include <qinputdialog.h>

MtpBrowser::MtpBrowser(QWidget *parent, const char *name) : QTextBrowser(parent,name) {
    setTextFormat(Qt::RichText);

    m_bookpop = new QPopupMenu(this);
    m_delpop = new QPopupMenu(this);
    connect(m_bookpop,SIGNAL(activated(int)),this,SLOT(slotGoto(int)));
    connect(m_delpop,SIGNAL(activated(int)),this,SLOT(slotDelete(int)));
}

MtpBrowser::~MtpBrowser() {}

QPopupMenu* MtpBrowser::createPopupMenu(const QPoint& pos) {
    m_point = pos;

    m_pop = new QPopupMenu(this);
    m_pop->insertItem("&Copy",this,SLOT(copy()),CTRL+Key_C);
    m_pop->insertItem("Select all",this,SLOT(selectAll()));
    m_pop->insertItem("Bookmark",this,SLOT(slotBookmark()));
    m_pop->insertItem("Goto...",m_bookpop);
    m_pop->insertItem("Delete...",m_delpop);
    return m_pop;
}

void MtpBrowser::slotBookmark(const QString& name) {
    placeCursor(name.isNull()?m_point:this->viewportToContents(QPoint(0,0)));
    int para, index;
    getCursorPosition(&para,&index);
    QString bname = name.isNull()?QInputDialog::getText("Bookmark","Enter a name for bookmark :"):name;

    if(m_names.find(bname) == m_names.end()) {
        m_delpop->insertItem(bname);
        m_names.insert(bname,m_bookpop->insertItem(bname));
    }
    m_marks.insert(bname,QPair<int,int>(para,index));
}

void MtpBrowser::slotGoto(int id) {
    slotGoto(m_bookpop->text(id));
}

void MtpBrowser::slotGoto(const QString& label) {
    QPair<int,int> pos = *m_marks.find(label);
    setCursorPosition(pos.first, pos.second);
}

void MtpBrowser::slotDelete(int id) {
    QString bname = m_delpop->text(id);
    m_marks.remove(bname);
    m_delpop->removeItem(id);
    m_bookpop->removeItem(*m_names.find(bname));
    m_names.remove(bname);
}
