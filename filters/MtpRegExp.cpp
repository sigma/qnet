/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "MtpRegExp.h"
#include "MtpContext.h"

//#include <iostream>

MtpRegExp::MtpRegExp(const QString & pat, MtpContext * ctxt) {
    pattern = pat;
    m_context = ctxt;
}

MtpRegExp::~MtpRegExp() {}

bool MtpRegExp::exactMatch(const QString & str) {

    QString res(pattern);
    if (m_context) {
        QRegExp rx( "\\\\(\\w+)\\\\" );
        QStringList list;

        int pos = 0;
        while ( pos >= 0 ) {
            pos = rx.search( pattern, pos );
            if ( pos > -1 ) {
                list += rx.cap( 1 );
                pos  += rx.matchedLength();
            }
        }
        for (QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
            QString value;
            if ((value = m_context->getValue(*it)) != QString::null)
                res = res.replace(QRegExp("\\\\" + *it + "\\\\"),value);
            else
                return false;
        }
    }

    reg = QRegExp(res);
    reg.setCaseSensitive(false);
    return reg.exactMatch(str);
}

QString MtpRegExp::cap(int i) {
    return reg.cap(i);
}

int MtpRegExp::search(const QString & msg, int & n) const {
    return reg.search(msg,n);
}

int MtpRegExp::matchedLength() const {
    return reg.matchedLength();
}
