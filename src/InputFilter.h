/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _INPUTFILTER_H_
#define _INPUTFILTER_H_

#include "Filter.h"
#include <qregexp.h>

/**
 * 
 * Yann Hodique
 **/
class InputFilter : public Filter
{

public:
  InputFilter(QString & name, bool memory = false, MtpContext * ctxt = 0);
  ~InputFilter();
  
  bool memorize();
  bool applyTo(QString &);
  
  void setRegExp(QString &);
  void setResultPattern(QString &);
  
private:
	bool memory;
        MtpRegExp reg;
        QString pattern;
        MtpContext * m_context;
};

#endif
