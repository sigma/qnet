/*  Time-stamp: <13/02/2005 11:43:13 Yann Hodique>  */

/**
 *  @file colorizerlist.h
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

#ifndef _COLORIZERLIST_H_
#define _COLORIZERLIST_H_

#include <QList>

#include "colorizer.h"

/**
 * \addtogroup fontification
 * @{
 */

/**
 * List of Colorizer. Provides a partition over a piece of text to apply
 * fontification on it.
 *
 * \sa Colorizer
 *
 */
class ColorizerList : public QList<Colorizer> {
public:
/**
 * Constructor
 *
 */
    ColorizerList() {}

/**
 * Destructor
 *
 */
    ~ColorizerList() {}

/**
 * Simplify the list. Reorder and rearrange the list so that it represents a
 * partition of the string if should fontify.
 *
 * @todo implement this method
 *
 * @return the simplified list
 */
    ColorizerList& simplify();
};

/**
 * @}
 */

#endif /* _COLORIZERLIST_H_ */
