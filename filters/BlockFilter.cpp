/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "BlockFilter.h"


BlockFilter::BlockFilter(const QString & name, MtpContext * ctxt) : Filter(name,ctxt) {
    dependency = 0;
    m_context = ctxt;
}


BlockFilter::~BlockFilter() {}

bool BlockFilter::applyTo(QString & msg, Position pos) {
    switch (pos) {
    case BEGIN: {
        MtpRegExp re(beg_reg);
        bool match = re.exactMatch(msg);

        if (match) {
            setResult(applyProcessedRegexpToPattern(re,begin_pattern));
            finished = false;
        }

        return match;
    }
    case IN: {
        MtpRegExp re(end_reg);
        bool match_test = re.exactMatch(msg);

        if (match_test) {
            finished = true;
            setResult(applyProcessedRegexpToPattern(re,end_pattern));
        }
        else {
            MtpRegExp re(main_reg);
            bool match = re.exactMatch(msg);

            if (match)
                setResult(applyProcessedRegexpToPattern(re,main_pattern));
            else
                setResult(msg);
        return match;
        }
    }}
    return false;
}

void BlockFilter::setInputDependency(InputFilter * in) {
    dependency = in;
}

void BlockFilter::setBeginRegExp(const QString& reg) {
    begin = reg;
    this->beg_reg = MtpRegExp(reg,m_context);
}

void BlockFilter::setMainRegExp(const QString& reg) {
    main = reg;
    this->main_reg = MtpRegExp(reg,m_context);
}

void BlockFilter::setEndRegExp(const QString& reg) {
    end = reg;
    this->end_reg = MtpRegExp(reg,m_context);
}

InputFilter * BlockFilter::getInputDependency() {
    return dependency;
}

bool BlockFilter::isFinished() const {
    return finished;
}

void BlockFilter::setResultPattern(const QString& pat) {
    this->main_pattern = pat;
}

void BlockFilter::setBeginPattern(const QString& pat) {
    this->begin_pattern = pat;
}

void BlockFilter::setEndPattern(const QString& pat) {
    this->end_pattern = pat;
}

QString BlockFilter::getBeginRegExp() const {
    return begin;
}

QString BlockFilter::getMainRegExp() const {
    return main;
}

QString BlockFilter::getEndRegExp() const {
    return end;
}

QString BlockFilter::getResultPattern() const {
    return main_pattern;
}

QString BlockFilter::getBeginPattern() const {
    return begin_pattern;
}

QString BlockFilter::getEndPattern() const {
    return end_pattern;
}
