/***************************************************************************
 *   Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.           *
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include <iostream>
#include <qapplication.h>
#include <qdir.h>
#include <unistd.h>

#include "mainwin.h"
#include "qnet.h"

#ifdef GUILE
#include "qnet_guile_wrap.cxx"
#include <scm.h>
#endif

MainWin * main_window;

#ifdef GUILE
void guile_global_init() {
    Scm *scm = Scm::getInstance();
    scm->createHook("chatsession-created-hook",0);
    scm->createHook("chatsession-output-hook",1);
}
#endif

int main( int argc, char ** argv ) {
    QApplication a( argc, argv );
    QString rc;

#ifdef GUILE
    Scm *scm = Scm::getInstance();

    scm_init_guile();
    scm_init_internal_module();

    guile_global_init();
#endif

    while (1)
    {
        char c = getopt(argc, argv, "f:");
        if (c == (char)-1) break;
        switch (c)
        {
            case 'f':
                rc = optarg;
                break;
            default:
                break;
        }
    }
    main_window = new MainWin(false,false,"main_window",rc);
    main_window->setUseDock();

#ifdef GUILE
    scm->loadFile(QDir::homeDirPath() + "/.qnet.scm");
#endif

    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    a.connect( main_window, SIGNAL(closeProgram()), &a, SLOT(quit()) );

    return a.exec();
}
