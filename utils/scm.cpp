/*
 *  File: scm.cpp
 *  Created: Saturday, October 2, 2004
 *  Time-stamp: <26/10/2004 11:37:39 Yann Hodique>
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

extern "C" {
    SCM _load_file(void * filename) {
        return scm_primitive_load(scm_makfrom0str((char*) filename));
    }

    SCM _run_hook(void * data) {
        SCM** d = (SCM**)data;
        return scm_run_hook(*(d[0]),*(d[1]));
    }
}

SCM Scm::loadFile(const QString& filename) {
    return protect(_load_file,(void*)filename.ascii());
}

SCM Scm::runHook(const QString& hook, ScmList args) {
    SCM* data[2];
    SCM h = resolve(hook);
    SCM a = SCM_EOL;

    for(ScmList::ConstIterator it = args.begin(); it != args.end(); ++it)
        a = scm_cons(*it,a);

    data[0] = &h;
    data[1] = &a;

    return protect(_run_hook,data);
}

void Scm::createHook(const QString& symb, unsigned int nbargs) {
    SCM hook=scm_make_hook(SCM_MAKINUM(nbargs));
    scm_c_define(symb.ascii(),hook);
    sym[symb] = hook;
}

SCM Scm::resolve(const QString& symb) {
    return sym[symb];
}

SCM Scm::protect(scm_t_catch_body body, void *body_data) {
    return scm_internal_catch (SCM_BOOL_T,
                               body, body_data,
                               scm_handle_by_message_noexit, NULL);
}
