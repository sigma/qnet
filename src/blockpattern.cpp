/*  Time-stamp: <08/02/2005 09:14:05 Yann Hodique>  */

/**
 *  @file blockpattern.cpp
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

#include "blockpattern.h"

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
    return reg.exactMatch(text);
}
