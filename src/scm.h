/*  Time-stamp: <13/02/2005 11:29:28 Yann Hodique>  */

/**
 *  @file scm.h
 *  @date Saturday, October 2, 2004
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

#ifndef _SCM_H_
#define _SCM_H_

#include <libguile.h>

#include <QString>
#include <QMap>

class ScmList: public QList<SCM> {
public:
    ScmList& operator<< (const QString& msg) {
        append(scm_makfrom0str(msg.ascii()));
        return *this;
    }
};

/**
 * Singleton class for handling interaction between C++ code and
 * Guile. Provides several utilities for wrapping common lisp actions
 *
 */
class Scm {
public:

/**
 * This method returns an instance (since the class is a singleton, there is no
 * way to create it by yourself).
 *
 *
 * @return the instance
 */
    static Scm *getInstance();

    typedef QMap<QString,SCM> SymbolsMap;

/**
 * Load a file into the embedded guile interpreter. This function is a wrapper
 * around scm_primitive_load().
 *
 * @param filename the file to load
 *
 * @return the result of scm_primitive_load
 */
    SCM loadFile(const QString& filename) const;

/**
 * Run a hook with some arguments. This function is a wrapper around
 * scm_run_hook().
 *
 * @param name name of the hook
 * @param argv arguments vector
 *
 * @return the result of scm_run_hook()
 */
    SCM runHook(const QString& name, const ScmList& argv) const;

/**
 * Create a new hook with fixed arity.
 *
 * @param name name of the hook
 * @param argc number of arguments the hook should be run with
 *
 * @return the hook as SCM object
 */
    SCM createHook(const QString& name, unsigned int argc);

/**
 * Create a variable holding a value.
 *
 * @param name name of the variable
 * @param value associated value
 */
    void createVar(const QString& name, SCM value = SCM_EOL);

/**
 * Resolve a local symbol into its corresponding SCM object.
 *
 * @param symbol symbol to resolve
 *
 * @return associated SCM object
 */
    SCM resolve(const QString& symbol) const;

/**
 * Evaluate an expression at the top-level. This function is a wrapper around
 * scm_primitive_eval().
 *
 * @param expr the expression to evaluate
 *
 * @return the result of scm_primitive_eval()
 */
    SCM eval(SCM expr) const;

private:
    Scm();
    ~Scm() {};

    SCM protect(scm_t_catch_body body, void *body_data) const;

    static Scm *m_scm;

    SymbolsMap sym;
};	// end of class Scm


#endif /* _SCM_H_ */
