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


BlockFilter::BlockFilter(QString & name, MtpContext * ctxt) : Filter(name) {
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
            setResult(applyProcessedRegexpToPattern(re,pattern));
            finished = false;
        }
            
        return match;
    }    
    case IN: {
        MtpRegExp re("^(<.*>)?([^<>]+)(<.*>)?");
        bool match = re.exactMatch(msg);

        if (match)
            setResult(applyProcessedRegexpToPattern(re,pattern));

        MtpRegExp test(end_reg);
        bool match_test = test.exactMatch(msg);

        if (match_test)
            finished = true;
        
        return match;
        }
    }
    return false;
}

void BlockFilter::setInputDependency(InputFilter * in) {
    dependency = in;
}

void BlockFilter::setBeginRegExp(QString reg) {
    this->beg_reg = MtpRegExp(reg,m_context);
}

void BlockFilter::setEndRegExp(QString reg) {
    this->end_reg = MtpRegExp(reg,m_context);
}

InputFilter * BlockFilter::getInputDependency() {
    return dependency;
}

bool BlockFilter::isFinished() {
    return finished;
}

void BlockFilter::setResultPattern(QString pat) {
    this->pattern = pat;
}
