/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _GLOBALFILTER_H_
#define _GLOBALFILTER_H_

#include "Filter.h"

/**
 * 
 * Yann Hodique
 **/
class GlobalFilter : public Filter
{

public:
  GlobalFilter(QString & name);
  ~GlobalFilter();  
  
  bool applyTo(QString &);
  void setResultPattern(QString &);
  
  private:
  QString pattern;
};

#endif
