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

#include "ChatSession.h"

/**
 * 
 * Yann Hodique
 **/
class Page : public QWidget
{
  Q_OBJECT

public:
  Page(QWidget *parent, const char *name, ChatSession *master);
  virtual ~Page();
  
  ChatSession * getMaster();
  
  virtual void append(QString &) = 0;
  
private:
 ChatSession * m_master;
 
 signals:
	void textDisplayed(QWidget *);
};

#endif
