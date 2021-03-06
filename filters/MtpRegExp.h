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

/**
 *
 * Yann Hodique
 **/

class MtpContext;

class MtpRegExp {

public:
    MtpRegExp(const QString & = "", MtpContext * ctxt = 0);
    ~MtpRegExp();

    bool exactMatch(const QString &);
    QString cap(int i);
    int search(const QString&,int&) const;
    int matchedLength() const;

private:
    QRegExp reg;
    QString pattern;
    MtpContext * m_context;
};

#endif
