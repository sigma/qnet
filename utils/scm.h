/*
 *  File: scm.h
 *  Created: Saturday, October 2, 2004
 *  Time-stamp: <26/10/2004 11:51:45 Yann Hodique>
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

#include <libguile.h>

#include <qstring.h>
#include <qmap.h>

class ScmList: public QValueList<SCM> {
public:
    ScmList& operator<< (const QString& msg) {
        ((QValueList<SCM>)(*this)) << scm_makfrom0str(msg.ascii());
        return *this;
    }
};

class Scm {
public:

    static Scm *getInstance();

    typedef QMap<QString,SCM> SymbolsMap;

    SCM loadFile(const QString&);
    SCM runHook(const QString&, ScmList);
    void createHook(const QString&, unsigned int);
    SCM resolve(const QString&);

private:
    Scm();
    ~Scm() {};

    SCM protect(scm_t_catch_body body, void *body_data);

    static Scm *m_scm;
    static bool instantiated;

    SymbolsMap sym;
};	// end of class Scm


#endif /* _SCM_H_ */
