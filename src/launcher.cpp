/*
 *  File: launcher.cpp
 *  Created: Tuesday, December 28, 2004
 *  Time-stamp: <20/01/2005 20:50:26 Yann Hodique>
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
#include "mtpsocket.h"

void Launcher::init() {
    MtpSocket * s = new MtpSocket(this);
    s->setHost("localhost");
    s->setPort(5000);
    s->setLogin("plop");
    s->setPasswd("plop");

    MtpProtocol * mp = new MtpProtocol(this);
    mp->installIO(s);

    connect(mp, SIGNAL(loginQuery()),
            s, SLOT(sendLogin()));
    connect(mp, SIGNAL(passwdQuery()),
            s, SLOT(sendPasswd()));

    d = new Dispatcher(mp,this);

    MainWindow * mw = qt_cast<MainWindow*>(mainWidget());
    if(mw) {
        FloatingTab * ft = qt_cast<FloatingTab*>(mw->centralWidget());
        ed = new MtpArea;
        if(ft) {
            ft->addTab(ed,"plip");
            d->addInteractionArea(ed);
           MtpArea *ed2 = new MtpArea;
           ft->addTab(ed2,"plop");
           d->addInteractionArea(ed2);
        }
    }

    s->connectToHost();
}
