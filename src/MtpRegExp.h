/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _MTPREGEXP_H_
#define _MTPREGEXP_H_

#include <qstring.h>
#include <qregexp.h>

#include "MtpContext.h"

/**
 * 
 * Yann Hodique
 **/
class MtpRegExp {

public:
    MtpRegExp(const QString & = "", MtpContext * ctxt = 0);
    ~MtpRegExp();
    
    bool exactMatch(QString &);
    QString cap(int i);
    int search(QString&,int&);
    int matchedLength();


private:
    QRegExp reg;
    QString pattern;
    MtpContext * m_context;
};

#endif
