/*  Time-stamp: <09/02/2005 19:19:47 Yann Hodique>  */

/**
 *  @file main.cpp
 *  @date Monday, February 7, 2005
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

/**
 * \mainpage QNet2 project.
 * This project consists of several parts.
 *
 * \section cpp C++ part
 * \section lisp Lisp part
 *
 */

#include "scm.h"
#include "mainwindow.h"

#include <QApplication>


MainWindow * mw;

extern "C" {
    void scm_init_internal_module(void);
}

void guile_global_init() {
//     Scm *scm = Scm::getInstance();
//     scm->createHook("chatsession-created-hook",0);
//     scm->createHook("chatsession-output-hook",1);
}

int main(int argc, char **argv)
{
    QString rc;
    Scm *scm = Scm::getInstance();

    scm_init_guile();
    scm_init_internal_module();

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

    QApplication app(argc, argv);
    mw = new MainWindow(0,0,false);
    app.setMainWidget(mw);
    mw->show();

    scm->loadFile(QDir::homePath() + "/.qnet2.scm");

    return app.exec();
}
