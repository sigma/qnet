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

#include "qnet_guile_wrap.cxx"
#include "guile_global.h"

MainWin * main_window;

SCM init(void *) {
    return scm_primitive_load(scm_makfrom0str((QDir::homeDirPath() + "/.qnet.scm").ascii()));
}

void guile_global_init() {
    guile_chatsession_created_hook=scm_make_hook(SCM_MAKINUM(0));
    scm_c_define("chatsession-created-hook",guile_chatsession_created_hook);
}

int main( int argc, char ** argv ) {
    QApplication a( argc, argv );
    QString rc;

    scm_init_guile();
    SWIG_init();
    guile_global_init();

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

    scm_internal_catch (SCM_BOOL_T,
                        init, NULL,
                        scm_handle_by_message_noexit, NULL);

    main_window->setUseDock();

    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    a.connect( main_window, SIGNAL(closeProgram()), &a, SLOT(quit()) );

    return a.exec();
}
