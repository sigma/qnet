/*
 *  File: scm.cpp
 *  Created: Saturday, October 2, 2004
 *  Time-stamp: <02/10/2004 10:11:45 Yann Hodique>
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

#include "scm.h"

bool Scm::instantiated = false;
Scm* Scm::m_scm = 0;

Scm::Scm() {}

Scm::~Scm() {}

Scm* Scm::getInstance()
{
    if(! instantiated) {
        m_scm = new Scm();
        instantiated = true;
        return m_scm;
    } else {
        return m_scm;
    }
}
