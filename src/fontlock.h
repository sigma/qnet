/*  Time-stamp: <13/02/2005 12:02:52 Yann Hodique>  */

/**
 *  @file fontlock.h
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

#ifndef _FONTLOCK_H_
#define _FONTLOCK_H_

#include <QStack>

#include "blockpattern.h"

/**
 * \addtogroup fontification
 * @{
 */

/**
 * Class for colorizing a text. Inspired by the old QSyntaxHighlighter class
 *
 */
class FontLock {
public:

/**
 * Constructor
 *
 */
    FontLock();

/**
 * Destructor
 *
 */
    ~FontLock();

/**
 * Highlight a portion of text according to the current block. Blocks can be
 * nested if needed. The result of the previous highlightParagraph() invocation
 * (or 0) should be passed as \a block argument.
 *
 * @param text text to highlight
 * @param block current block or 0 if none
 * @param cursor cursor where to insert \a text
 *
 * @return new current block or 0 if none
 */
    int highlightParagraph(const QString& text, int block, QTextCursor& cursor);

/**
 * Add a new Pattern to recognize. This Pattern is for single lines only.
 *
 * @param pat the pattern to add
 */
    void addPattern(const Pattern& pat);

/**
 * Add a new BlockPattern to recognize. This BlockPattern is for multiple lines only.
 *
 * @param pat the pattern to add
 */
    void addMultiLinePattern(const BlockPattern& pat);

/**
 * Empty the list of patterns that are recognized by the current FontLock
 *
 */
    void clear();

/**
 * Redo the highlighting according to the new rules
 *
 */
    void rehighlight();

private:
    QList<Pattern> m_lines;
    QList<BlockPattern> m_blocks;

    QStack<int> m_nested;

};	// end of class FontLock

/**
 * @}
 */

#endif /* _FONTLOCK_H_ */
