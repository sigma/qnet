/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "GlobalFilter.h"


GlobalFilter::GlobalFilter(const QString & name) : Filter(name)
{}


GlobalFilter::~GlobalFilter() {}

bool GlobalFilter::applyTo(QString & msg) {
    MtpRegExp re(".*");

    bool match = re.exactMatch(msg);

    if (match)
        setResult(applyProcessedRegexpToPattern(re,pattern));

    return match;
}

void GlobalFilter::setResultPattern(const QString & pat) {
    pattern = pat;
}
