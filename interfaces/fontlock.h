/*
 *  File: fontlock.h
 *  Created: Tuesday, August 24, 2004
 *  Time-stamp: <03/10/2004 21:15:36 Yann Hodique>
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

#ifndef _FONTLOCK_H_
#define _FONTLOCK_H_

#include <qsyntaxhighlighter.h>
#include <qtextedit.h>
#include <qregexp.h>
#include <qvaluestack.h>

class Face {
public:
    Face() {} //the default constructor()
    Face(const QFont& font) : m_font(font) {}
    Face(const QColor& color) : m_color(color) {}
    Face(const QFont& font, const QColor& color) : m_font(font), m_color(color) {}
    Face(const QString& family, const QString& color, int size = 12, int weight = QFont::Normal, int italic = 0) : m_font(family,size,weight,italic), m_color(color) {}

    ~Face() {} //the destructor

    const QFont font() const {return m_font;}
    const QColor color() const {return m_color;}

private:
    QFont m_font;
    QColor m_color;
};	// end of class Face

class Colorizer {
public:
    Colorizer() {} //the default constructor()
    Colorizer(int start, int length, Face face) : m_start(start), m_length(length), m_face(face) {}

    ~Colorizer() {} //the destructor

    int start() const {return m_start;}
    int length() const {return m_length;}
    const Face face() const {return m_face;}

private:
    int m_start, m_length;
    Face m_face;
};	// end of class Colorizer

class ColorizerList : public QValueList<Colorizer> {
public:
    ColorizerList() {} //the default constructor()

    ~ColorizerList() {} //the destructor

    ColorizerList simplify() const;
};

class Pattern {
public:
    Pattern() {} //the default constructor()
    Pattern(const QRegExp& reg) : m_reg(reg) {}
    Pattern(const QString& str) : m_reg(QRegExp(str)) {}

    ~Pattern() {} //the destructor

    typedef QPair< int,Face > MatchPair;
    Pattern& operator<< (const MatchPair& p) {
        m_matches << p; return *this;
    }

    void add(int i, Face f) {
        *this << qMakePair(i,f);
    }

    bool match(const QString& text);

    ColorizerList getColors() const {return m_colors;}

private:
    QRegExp m_reg;
    QValueList<MatchPair> m_matches;
    ColorizerList m_colors;
};	// end of class Pattern

class BlockPattern {
public:
    BlockPattern() {} //the default constructor()
    BlockPattern(const Pattern& b, const Pattern &e, const Pattern &m)
        : m_begin(b), m_end(e), m_middle(m) {}

    ~BlockPattern() {} //the destructor

    bool matchBegin(const QString& text);
    bool matchEnd(const QString& text);
    bool matchMiddle(const QString& text);

//    ColorizerList getColors() const {return m_colors;}
    Pattern begin() {return m_begin;}
    Pattern end() {return m_end;}
    Pattern middle() {return m_middle;}


private:
    Pattern m_begin, m_end, m_middle;
//    ColorizerList m_colors;

    bool internalMatch(Pattern&, const QString&);
};	// end of class BlockPattern


class FontLock : public QSyntaxHighlighter{

public:
    FontLock(QTextEdit *edit); //the default constructor()

    ~FontLock(); //the destructor

    int highlightParagraph(const QString& text, int block);

    void addPattern(const Pattern&);

    void addMultiLinePattern(const BlockPattern&);

    void clear();

private:
    QValueList<Pattern> m_lines;
    QValueList<BlockPattern> m_blocks;

    QValueStack<int> m_nested;

};	// end of class FontLock


#endif /* _FONTLOCK_H_ */
