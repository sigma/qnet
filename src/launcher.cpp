/*
 *  File: launcher.cpp
 *  Created: Tuesday, December 28, 2004
 *  Time-stamp: <31/12/2004 12:04:07 Yann Hodique>
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

#include "launcher.h"
#include "dispatcher.h"

void Launcher::init() {
    MtpProtocol * mp = new MtpProtocol(this);
    mp->setHost("localhost");
    mp->setPort(5000);
    mp->setLogin("plop");
    mp->setPasswd("plop");

    d = new Dispatcher(mp,this);

    MainWindow * mw = qt_cast<MainWindow*>(mainWidget());
    if(mw) {
        FloatingTab * ft = qt_cast<FloatingTab*>(mw->centralWidget());
        ed = new MtpArea;
        if(ft) {
            ft->addTab(ed,"plip");
            d->addInteractionArea(ed);
//            MtpArea *ed2 = new MtpArea;
//            ft->addTab(ed2,"plop");
//            d->addInteractionArea(ed2);
        }
    }

    mp->connectToHost();
}
