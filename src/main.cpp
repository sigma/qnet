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

#include "mainwin.h"
#include "qnet.h"

int main( int argc, char ** argv ) {
    QApplication a( argc, argv );
    QString rc;

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
    MainWin* m = new MainWin(false,false,"main_window",rc);
    m->setUseDock();

    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    a.connect( m, SIGNAL(closeProgram()), &a, SLOT(quit()) );

    return a.exec();
}
