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
#include "MtpContext.h"

Filter::Filter(const QString & name, MtpContext * ctxt) {
    this->name = name;
    this->m_context = ctxt;
}


Filter::~Filter() {}

void Filter::setPolicy(Policy p) {
    this->pol = p;
}

Filter::Policy Filter::policy() const {
    return this->pol;
}

bool Filter::isEnabled() const {
    return this->active;
}

void Filter::setEnabled(bool b) {
    this->active = b;
}

void Filter::enable() {
    this->active = true;
}

void Filter::disable() {
    this->active = false;
}

QString Filter::getName() const {
    return name;
}

QString Filter::getResult() const {
    return result;
}

void Filter::setResult(const QString& r) {
    result = r;
}

QString Filter::applyProcessedRegexpToPattern(MtpRegExp & re, const QString & pat) {
    QString res(pat);

//     if(m_context) {
//         QRegExp rx( "\\\\(\\w+)\\\\" );
//         QStringList list;

//         int pos = 0;
//         while ( pos >= 0 ) {
//             pos = rx.search( pat, pos );
//             if ( pos > -1 ) {
//                 list += rx.cap( 1 );
//                 pos  += rx.matchedLength();
//             }
//         }
//         for (QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
//             QString value;
//             if ((value = m_context->getValue(*it)) != QString::null)
//                 res = res.replace(QRegExp("\\\\" + *it + "\\\\"),value);
//         }
//     }

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
    for (QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
        QString repl(re.cap((*it).toInt()));
        res = res.replace(QRegExp("\\\\" + *it + "\\\\"),repl);
    }
    return res;
}

QString Filter::expandVars(const QString& msg, MtpContext * context) {
    QString res(msg);

    if(context) {
        QRegExp rx( "\\\\(\\w+)\\\\" );
        QStringList list;

        int pos = 0;
        while ( pos >= 0 ) {
            pos = rx.search( msg, pos );
            if ( pos > -1 ) {
                list += rx.cap( 1 );
                pos  += rx.matchedLength();
            }
        }
        for (QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
            QString value;
            if ((value = context->getValue(*it)) != QString::null)
                res = res.replace(QRegExp("\\\\" + *it + "\\\\"),value);
        }
    }
    return res;
}
