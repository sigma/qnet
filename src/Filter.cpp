/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "Filter.h"


Filter::Filter(QString & name, MtpContext * ctxt) {
    this->name = name;
    this->m_context = ctxt;
}


Filter::~Filter() {}

void Filter::setPolicy(Policy p) {
    this->pol = p;
}

Filter::Policy Filter::policy() {
    return this->pol;
}

bool Filter::isEnabled() {
    return this->active;
}

void Filter::enable() {
    this->active = true;
}

void Filter::disable() {
    this->active = false;
}

QString Filter::getName() {
    return name;
}

QString Filter::getResult() {
    return result;
}

void Filter::setResult(QString r) {
    result = r;
}

QString Filter::applyProcessedRegexpToPattern(MtpRegExp & re, const QString & pat) {
    QString res(pat);

    if(m_context) {
        QRegExp rx( "\\\\(\\w+)\\\\" );
        QStringList list;

        int pos = 0;
        while ( pos >= 0 ) {
            pos = rx.search( pat, pos );
            if ( pos > -1 ) {
                list += rx.cap( 1 );
                pos  += rx.matchedLength();
            }
        }
        for (QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
            QString value;
            if ((value = m_context->getValue(*it)) != QString::null)
                res = res.replace(QRegExp("\\\\" + *it + "\\\\"),value);
        }
    }

    QRegExp rx( "\\\\(\\d+)\\\\" );
    QStringList list;

    int pos = 0;
    while ( pos >= 0 ) {
        pos = rx.search( pat, pos );
        if ( pos > -1 ) {
            list += rx.cap( 1 );
            pos  += rx.matchedLength();
        }
    }
    for (QStringList::Iterator it = list.begin(); it != list.end(); ++it)
        res = res.replace(QRegExp("\\\\" + *it + "\\\\"),re.cap((*it).toInt()));
    return res;
}
