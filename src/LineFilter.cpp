/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "LineFilter.h"


LineFilter::LineFilter(QString & name, MtpContext * ctxt) : Filter(name,ctxt)
{
m_context = ctxt;
}


LineFilter::~LineFilter()
{
}

bool LineFilter::applyTo(QString & msg) {
MtpRegExp re(reg);
bool match = re.exactMatch(msg);

if (match) setResult(applyProcessedRegexpToPattern(re,pattern));

return match;
}

void LineFilter::setRegExp(QString reg) {
	this->reg = MtpRegExp(reg,m_context);
}

void LineFilter::setResultPattern(QString pat) {
	this->pattern = pat;
}
