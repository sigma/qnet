/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "InputFilter.h"


InputFilter::InputFilter(QString & name, bool memory, MtpContext * ctxt)
  : Filter(name)
{
this->memory = memory;
m_context = ctxt;
}


InputFilter::~InputFilter()
{
}

bool InputFilter::applyTo(QString & msg) {
MtpRegExp re(reg);
bool match = re.exactMatch(msg);

if (match) setResult(applyProcessedRegexpToPattern(re,pattern));

return match;
}

bool InputFilter::memorize() {
return memory;
}

void InputFilter::setRegExp(QString & exp) {
reg = MtpRegExp(exp,m_context);
}

void InputFilter::setResultPattern(QString & pat) {
pattern = pat;
}
