/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _MTPBROWSER_H_
#define _MTPBROWSER_H_

#include <qwidget.h>
#include <qstring.h>
#include <qtextbrowser.h>

class QPopupMenu;

/**
 * 
 * Yann Hodique
 **/
class MtpBrowser : public QTextBrowser
{
  Q_OBJECT

public:

  MtpBrowser(QWidget *parent, const char *name);
  ~MtpBrowser();
  QPopupMenu* createPopupMenu(const QPoint& pos);
  
  QString getText() { return text();}
  
  public slots:
      void setSource(const QString &) {}
  void slotBookmark();
  void slotGoto(int id);
  void slotDelete(int id);
  
private:
  QPopupMenu *m_pop, *m_bookpop, *m_delpop;
  QPoint m_point;
  QMap<QString, QPair<int,int> > m_marks;
  QMap<QString,int> m_names;
};

#endif
