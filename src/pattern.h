/*  Time-stamp: <13/02/2005 18:37:00 Yann Hodique>  */

/**
 *  @file pattern.h
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

#ifndef _PATTERN_H_
#define _PATTERN_H_

#include <QPair>

#include "colorizerlist.h"

/**
 * \addtogroup fontification
 * @{
 */

/**
 * The Pattern class represents the fontification unit. A line of text is
 * transformed into a fontified one, when matching a given regexp.
 *
 * \sa BlockPattern
 *
 */
class Pattern {
public:

/**
 * Constructor
 *
 */
    Pattern() {} //the default constructor()

/**
 * Constructor
 *
 * @param reg regexp that defines the Pattern
 *
 * \sa Pattern(const QString& str)
 */
    Pattern(const QRegExp& reg) : m_reg(reg) {}

/**
 * Constructor
 *
 * @param str regexp (as string) that defines the Pattern
 *
 * \sa Pattern(const QRegExp& reg)
 */
    Pattern(const QString& str) : m_reg(QRegExp(str)) {}

/**
 * Destructor
 *
 */
    ~Pattern() {} //the destructor

/**
 * Association between a number (the index of a match from the regexp) and a
 * Face to apply to this match
 *
 */
    typedef QPair< int,Face > MatchPair;

/**
 * Add a MatchPair to this Pattern.
 *
 * @param p the MatchPair to append
 *
 * @return the modified Pattern
 *
 * \sa add()
 */
    Pattern& operator<< (const MatchPair& p) {
        m_matches << p; return *this;
    }

/**
 * Add a MatchPair to this Pattern.
 *
 * @param i index of the match
 * @param f Face to apply
 *
 * \sa operator<<()
 */
    void add(int i, Face f) {
        *this << qMakePair(i,f);
    }

/**
 * Test a string against the Pattern
 *
 * @param text text to test
 *
 * @return true if \a text matches the Pattern
 */
    bool exactMatch(const QString& text);

/**
 * Access the result of the application of the Pattern : the fontification
 * list.
 *
 *
 * @return the ColorizerList to apply
 */
    ColorizerList getColors() const {return m_colors;}

private:
    QRegExp m_reg;
    QList<MatchPair> m_matches;
    ColorizerList m_colors;
};	// end of class Pattern

/**
 * @}
 */

#endif /* _PATTERN_H_ */
