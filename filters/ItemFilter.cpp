/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "ItemFilter.h"

//#include <iostream>

ItemFilter::ItemFilter(const QString & name, MtpContext * ctxt) : Filter(name,ctxt) {
    setPolicy(Filter::Final);
    m_context = ctxt;
}


ItemFilter::~ItemFilter() {}

bool ItemFilter::applyTo(QString & msg) {
    /*MtpRegExp re(reg);
    bool match = re.exactMatch(msg);

    if (match) setResult(applyProcessedRegexpToPattern(re,pattern));

    return match;
    */

    QRegExp rx(reg_exp);
    QString res("");
    int pos = 0;
    int tmp;


    while ( ((tmp = rx.search(msg, pos)) != -1) && rx.matchedLength() ) {
        //std::cout << "tmp = " << tmp << std::endl;
        //std::cout << "length = " << rx.matchedLength() << std::endl;
        res += msg.right(msg.length()-pos).left(tmp-pos);

        QString ok(msg.right(msg.length()-tmp).left(rx.matchedLength()));

        MtpRegExp re(reg);
        if (re.exactMatch(ok)) {
            res += applyProcessedRegexpToPattern(re,pattern);
        }
        pos = tmp;
        pos += rx.matchedLength();
    }
    res += msg.right(msg.length()-pos);
    setResult(res);

    return pos;

}

void ItemFilter::setRegExp(const QString& reg) {
    this->reg = MtpRegExp(reg, m_context);
    reg_exp = reg;
}

void ItemFilter::setResultPattern(const QString& pat) {
    this->pattern = pat;
}

QString ItemFilter::getRegExp() const {
    return reg_exp;
}

QString ItemFilter::getResultPattern() const {
    return pattern;
}
