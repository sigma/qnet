/*  Time-stamp: <08/02/2005 09:13:47 Yann Hodique>  */

/**
 *  @file pattern.cpp
 *  @date Monday, February 7, 2005
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

#include "pattern.h"

bool Pattern::exactMatch(const QString & text) {
    m_colors.clear();
    bool match = false;
    int offset = 0;

    while( (offset = m_reg.indexIn(text,offset) + 1) ) {
        match = true;
        for(QList<MatchPair>::const_iterator it = m_matches.begin(); it != m_matches.end(); ++it) {
            int num = (*it).first;
            int pos = m_reg.pos(num);
            if(pos != -1)
                m_colors << Colorizer(pos, m_reg.cap(num).length(), (*it).second);
        }
    }
    return match;
}
