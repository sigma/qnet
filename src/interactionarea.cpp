/*  Time-stamp: <09/02/2005 19:20:07 Yann Hodique>  */

/**
 *  @file interactionarea.cpp
 *  @date Thursday, December 30, 2004
 *  @author Yann Hodique <Yann.Hodique@lifl.fr>
 */

/************************************************************************
 *                                                                      *
 * This program is free software; you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 ************************************************************************/

#include "interactionarea.h"
#include "mtpoutput.h"

const QString InteractionArea::DefaultMatch = "^.*$";
const QString InteractionArea::DefaultReplace = "\\0";

InteractionArea::InteractionArea(QObject *parent) : QObject(parent) {
    setDisplayByDefault();
}

InteractionArea::~InteractionArea() {}

void InteractionArea::slotDisplay(const QString& str) {
    MtpOutput * out = getOutput();
    if(out) {
        QString msg = shouldDisplay(str);
        if (msg != QString::null)
            out->display(msg);
    }
}

void InteractionArea::slotSend(const QString& msg) {
    emit send(msg);
}

void InteractionArea::addPositiveFilter(const QString& beg, const QString& beg_repl,
                                        const QString& end, const QString& end_repl,
                                        const QString& middle, const QString& middle_repl) {
    addFilter(true, beg, beg_repl, end, end_repl, middle, middle_repl);
}

void InteractionArea::addNegativeFilter(const QString& beg, const QString& beg_repl,
                                        const QString& end, const QString& end_repl,
                                        const QString& middle, const QString& middle_repl) {
    addFilter(false, beg, beg_repl, end, end_repl, middle, middle_repl);
}

inline void InteractionArea::addFilter (bool type, const QString& beg, const QString& beg_repl,
                                        const QString& end, const QString& end_repl,
                                        const QString& middle, const QString& middle_repl) {
    Replacement repl;
    repl.begin = qMakePair(QRegExp(beg),beg_repl);
    if(end == QString::null) {
        (type?positive:negative) << repl;
    }
    else {
        repl.end = qMakePair(QRegExp(end),end_repl);
        repl.middle = qMakePair(QRegExp(middle),middle_repl);
        (type?positive_blocks:negative_blocks) << repl;
    }
}

QString InteractionArea::replace(QString from, QRegExp what, QString to) {
    QString to2 = to.replace(DefaultReplace,from);
    QString res = from.replace(what, to2);
    return res;
}

QString InteractionArea::shouldDisplay(const QString& txt) {
    QString msg(txt);
    QList<Replacement> &list = default_display ? negative : positive;
    QList<Replacement> &block_list = default_display ? negative_blocks : positive_blocks;

    if(m_nested.size()) {
        QRegExp re1 = block_list[m_nested.top()].end.first;
        QRegExp re2 = block_list[m_nested.top()].middle.first;
        if(re1.exactMatch(msg)) {
            QString res = !default_display ? replace(msg, re1, block_list[m_nested.top()].end.second) : QString::null;
            m_nested.pop();
            return res;
        } else if (re2.exactMatch(msg)) {
            return (!default_display) ? replace(msg, re2, block_list[m_nested.top()].middle.second) : QString::null;
        } else {
            m_nested.pop();
            return !default_display ? msg : QString::null;
        }
    }

    int index = 0;
    for(QList<Replacement>::ConstIterator it = block_list.begin(); it != block_list.end(); ++it, ++index)
        if((*it).begin.first.exactMatch(msg)) {
            m_nested.push(index);
            return !default_display ? replace(msg, (*it).begin.first, (*it).begin.second) : QString::null;
        }

    for(QList<Replacement>::ConstIterator it = list.begin(); it != list.end(); ++it) {
        if((*it).begin.first.exactMatch(msg))
            return !default_display ? replace(msg, (*it).begin.first, (*it).begin.second) : QString::null;
    }

    return default_display ? msg : QString::null;
}
