/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _LINEFILTER_H_
#define _LINEFILTER_H_

#include "Filter.h"

/**
 * 
 * Yann Hodique
 **/
class LineFilter : public Filter {

public:
    LineFilter(const QString & name, MtpContext * ctxt);
    ~LineFilter();

    void setRegExp(const QString& reg);
    void setResultPattern(const QString& pat);
    bool applyTo(QString &);

private:
    MtpRegExp reg;
    QString pattern;
    MtpContext * m_context;
};

#endif
