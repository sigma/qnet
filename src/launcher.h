/*
 *  File: launcher.h
 *  Created: Tuesday, December 28, 2004
 *  Time-stamp: <21/01/2005 17:44:37 Yann Hodique>
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

#ifndef _LAUNCHER_H_
#define _LAUNCHER_H_

#include <QApplication>

class Dispatcher;
class MtpArea;

/**
 * A temporary class for instantiating everything
 *
 */
class Launcher : public QApplication {

    Q_OBJECT

private:
    MtpArea *ed;
    Dispatcher *d;

public:
    Launcher(int & argc, char ** argv);
    ~Launcher();

/**
 * Init everything.
 *
 */
    void init();

};	// end of class Launcher


#endif /* _LAUNCHER_H_ */
