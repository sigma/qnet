/****************************************************************************
**
** Copyright (C) 1992-2004 Trolltech AS. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "launcher.h"
#include "scm.h"
#include "fontlock.h"
#include "mode.h"

MainWindow * main_window;

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

    Launcher app(argc, argv);
    main_window = new MainWindow(0,0,false);
    app.setMainWidget(main_window);
    main_window->show();

    Face f("fixed","black");
    Face::setDefaultFace(f);
    Mode *m = Mode::getMode("MtpBrowser");
    Pattern p1("Mtp");
    p1.add(0,Face("fixed","blue"));
    m->getFontLock()->addPattern(p1);
    Pattern p2("help");
    p2.add(0,Face("fixed","red"));
    m->getFontLock()->addPattern(p2);

    app.init();

    scm->loadFile(QDir::homePath() + "/.qnet2.scm");

    return app.exec();
}
