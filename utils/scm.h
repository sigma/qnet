/*
 *  File: scm.h
 *  Created: Saturday, October 2, 2004
 *  Time-stamp: <02/10/2004 10:11:35 Yann Hodique>
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

#ifndef _SCM_H_
#define _SCM_H_

class Scm {
public:

    static Scm *getInstance();

private:
    Scm(); //the default constructor()
    ~Scm(); //the destructor

    static Scm *m_scm;
    static bool instantiated;
};	// end of class Scm


#endif /* _SCM_H_ */
