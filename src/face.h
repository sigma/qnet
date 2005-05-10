/*  Time-stamp: <09/05/2005 18:17:27 Yann Hodique>  */

/**
 *  @file face.h
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

#ifndef _FACE_H_
#define _FACE_H_

#include <QFont>
#include <QColor>
#include <QTextCharFormat>

/**
 * \addtogroup fontification
 * @{
 */

/**
 * Main item for fontification. This class defines the font, size, aspect of a
 * character or string.
 *
 */
class Face {
public:
/**
 * Constructor
 *
 */
    Face() {}

/**
 * Construct a face with given font
 *
 * @param font the font to apply
 */
    Face(const QFont& font) : m_font(font) {
        tcf.setFont(font);
    }

/**
 * Construct a face with given color
 *
 * @param color the color to apply
 */
    Face(const QColor& color) : m_color(color) {
        tcf.setForeground(color);
    }

/**
 * Construct a face with given font and color
 *
 * @param font the font to apply
 * @param color the color to apply
 */
    Face(const QFont& font, const QColor& color) : m_font(font), m_color(color) {
        tcf.setFont(font);
        tcf.setForeground(color);
    }

/**
 * Available weights for faces
 *
 */
    typedef enum {
        Light = QFont::Light,   /**< light weight */
        Normal = QFont::Normal, /**< default weight */
        DemiBold = QFont::DemiBold, /**< semi-bold weight */
        Bold = QFont::Bold,     /**< bold weight  */
        Black = QFont::Black    /**< black weight */
    } Weight;

/**
 * Constructor with access to all face properties
 *
 * @param family font family
 * @param color the color to apply
 * @param size size of the font
 * @param weight weight of the font
 * @param italic true if font is italic
 */
    Face(const QString& family, const QString& color, int size = 12, int weight = Normal, bool italic = false) : m_font(family,size,weight,italic), m_color(color) {
        tcf.setFont(m_font);
        tcf.setForeground(QColor(color));
    }

    ~Face() {} //the destructor

    const QFont font() const {return m_font;}
    const QColor color() const {return m_color;}
    const QTextCharFormat textCharFormat() const {return tcf;}

/**
 * Access the face that is used in the default cases
 * \sa setDefaultFace(const Face& f)
 *
 * @return default face
 */
    static const Face& defaultFace() {return default_face;}

/**
 * Set the default face
 * \sa defaultFace()
 *
 * @param f new default face
 */
    static void setDefaultFace(const Face& f) {default_face = f;}

private:
    QFont m_font;
    QColor m_color;
    QTextCharFormat tcf;

    static Face default_face;
};	// end of class Face

/**
 * @}
 */

#endif /* _FACE_H_ */
