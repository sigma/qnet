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

#include <qapplication.h>
//#include <splash.h>

#include "qnet.h"
#include "version.h"

int main( int argc, char ** argv ) {
    QApplication a( argc, argv );

/*
    Splash *splash;
    splash = new Splash(0,0,0);
    QString msg("Ceci est un message de test un peu plus long que le précédent\navec un retour chariot en prime");
    splash->append(msg);
*/    
    QMtp * mw = new QMtp();
    mw->setCaption( CLIENT );
    
    mw->show();
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    
    return a.exec();
}
