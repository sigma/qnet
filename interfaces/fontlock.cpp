/*
 *  File: fontlock.cpp
 *  Created: Tuesday, August 24, 2004
 *  Time-stamp: <03/10/2004 20:50:09 Yann Hodique>
 *  Copyright: Yann Hodique
 *  Email: Yann.Hodique@lifl.fr
 */

/************************************************************************
 *                                                                      *
 * This program is free software; you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 ************************************************************************/

#include "fontlock.h"
#include <iostream>

// @todo implement this method
ColorizerList ColorizerList::simplify() const {
    return *this;
}

// bool Pattern::match(const QString & text) {
//     m_colors.clear();
//     if(! m_reg.exactMatch(text)) {
//         return false;
//     }

//     for(QValueList<MatchPair>::const_iterator it = m_matches.begin(); it != m_matches.end(); ++it) {
//         int num = (*it).first;
//         int pos = m_reg.pos(num);
//         if(pos != -1)
//             m_colors << Colorizer(pos, m_reg.cap(num).length(), (*it).second);
//     }
//     return true;
// }

bool Pattern::match(const QString & text) {
    m_colors.clear();
    bool match = false;
    int offset = 0;

    while( (offset = m_reg.search(text,offset) + 1) ) {
        match = true;
        for(QValueList<MatchPair>::const_iterator it = m_matches.begin(); it != m_matches.end(); ++it) {
            int num = (*it).first;
            int pos = m_reg.pos(num);
            if(pos != -1)
                m_colors << Colorizer(pos, m_reg.cap(num).length(), (*it).second);
        }
    }
    return match;
}

bool BlockPattern::matchBegin(const QString & text) {
    return internalMatch(m_begin,text);
}

bool BlockPattern::matchEnd(const QString & text) {
    return internalMatch(m_end,text);
}

bool BlockPattern::matchMiddle(const QString & text) {
    return internalMatch(m_middle,text);
}

bool BlockPattern::internalMatch(Pattern& reg, const QString & text) {
    return reg.match(text);
}

FontLock::FontLock(QTextEdit * edit) : QSyntaxHighlighter(edit) {}

FontLock::~FontLock() {}

int FontLock::highlightParagraph(const QString & text, int block) {
    ColorizerList list;
    if(block>0) {
        BlockPattern p = m_blocks[block-1];
        if(p.matchEnd(text)) {
            m_nested.pop();
            list = p.end().getColors();
        } else if(! p.matchMiddle(text)) { //error, emergency exit
            m_nested.pop();
            return highlightParagraph(text, m_nested.isEmpty() ? 0 : m_nested.top());
        } else {
            list = p.middle().getColors();
        }
    }

    int index = 0;
    for(QValueList<BlockPattern>::Iterator it = m_blocks.begin(); it != m_blocks.end(); ++it, ++index)
        if((*it).matchBegin(text)) {
            list += (*it).begin().getColors();
            m_nested.push(index+1);
        }

    for(QValueList<Pattern>::Iterator it = m_lines.begin(); it != m_lines.end(); ++it)
        if((*it).match(text))
            list += (*it).getColors();

    list = list.simplify();

    for(ColorizerList::const_iterator it = list.begin(); it != list.end(); ++it) {
        setFormat((*it).start(), (*it).length(), (*it).face().font(), (*it).face().color());
    }

    return m_nested.isEmpty() ? 0 : m_nested.top();
}

void FontLock::addPattern(const Pattern & p) {
    m_lines << p;

    rehighlight();
}

void FontLock::addMultiLinePattern(const BlockPattern & p) {
    m_blocks << p;

    rehighlight();
}

void FontLock::clear() {
    m_lines.clear();
    m_blocks.clear();
    m_nested.clear();

    rehighlight();
}
