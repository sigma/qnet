/*  Time-stamp: <13/02/2005 11:38:59 Yann Hodique>  */

/**
 *  @file blockpattern.h
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

#ifndef _BLOCKPATTERN_H_
#define _BLOCKPATTERN_H_

#include "pattern.h"

/**
 * \addtogroup fontification
 * @{
 */

/**
 * The BlockPattern class represents a block of text by its start (begin()),
 * end (end()) and main content (middle()).
 *
 * \sa Pattern
 *
 */
class BlockPattern {
public:
/**
 * Constructor
 *
 */
    BlockPattern() {} //the default constructor()

/**
 * Constructor
 *
 * @param b beginning-matching Pattern
 * @param e end-matching Pattern
 * @param m middle-matching Pattern
 */
    BlockPattern(const Pattern& b, const Pattern &e, const Pattern &m)
        : m_begin(b), m_end(e), m_middle(m) {}

/**
 * Destructor
 *
 */
    ~BlockPattern() {} //the destructor

/**
 * Test a string against the beginning of the BlockPattern
 *
 * @param text string to test
 *
 * @return true if text is a valid beginning for the BlockPattern
 */
    bool matchBegin(const QString& text);

/**
 * Test a string against the end of the BlockPattern
 *
 * @param text string to test
 *
 * @return true if text is a valid end for the BlockPattern
 */
    bool matchEnd(const QString& text);

/**
 * Test a string against the middle of the BlockPattern
 *
 * @param text string to test
 *
 * @return true if text is a valid middle for the BlockPattern
 */
    bool matchMiddle(const QString& text);

/**
 * Accessor. \sa BlockPattern(const Pattern& b, const Pattern &e, const Pattern &m)
 *
 */
    Pattern begin() {return m_begin;}

/**
 * Accessor. \sa BlockPattern(const Pattern& b, const Pattern &e, const Pattern &m)
 *
 */
    Pattern end() {return m_end;}

/**
 * Accessor. \sa BlockPattern(const Pattern& b, const Pattern &e, const Pattern &m)
 *
 */
    Pattern middle() {return m_middle;}


private:
    Pattern m_begin, m_end, m_middle;
//    ColorizerList m_colors;

    bool internalMatch(Pattern&, const QString&);
};	// end of class BlockPattern

/**
 * @}
 */

#endif /* _BLOCKPATTERN_H_ */
