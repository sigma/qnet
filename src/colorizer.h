/*  Time-stamp: <13/02/2005 11:39:28 Yann Hodique>  */

/**
 *  @file colorizer.h
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

#ifndef _COLORIZER_H_
#define _COLORIZER_H_

#include "face.h"

/**
 * \addtogroup fontification
 * @{
 */

/**
 * Simple class to define the fontification of a piece of text.
 *
 */
class Colorizer {
public:
/**
 * Constructor
 *
 */
    Colorizer() {}

/**
 * Constructor
 *
 * @param start starting position for this fontification
 * @param length length of the area to fontify
 * @param face face to apply
 */
    Colorizer(int start, int length, Face face) : m_start(start), m_length(length), m_face(face) {}

/**
 * Destructor
 *
 */
    ~Colorizer() {} //the destructor

/**
 * Accessor. \sa Colorizer(int start, int length, Face face)
 *
 */
    int start() const {return m_start;}

/**
 * Accessor. \sa Colorizer(int start, int length, Face face)
 *
 */
    int length() const {return m_length;}

/**
 * Accessor. \sa Colorizer(int start, int length, Face face)
 *
 */
    const Face face() const {return m_face;}

private:
    int m_start, m_length;
    Face m_face;

    bool operator< (const Colorizer& c) {
        return m_start < c.m_start;
    }

    friend class ColorizerList;
};	// end of class Colorizer

/**
 * @}
 */

#endif /* _COLORIZER_H_ */
