/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include <qregexp.h>
#include <qapplication.h>

#include "osdsplash.h"

PLUGIN_FACTORY(OsdSplash,"splash")

OsdSplash::OsdSplash(QWidget * /*parent*/, const char *name, Master * session)
    : Page(0, name, session) {
}

OsdSplash::~OsdSplash() {}

void OsdSplash::append(const QString & msg) {

    QRegExp re("\\[([NS]?)([EO]?)\\](.*)");
    if(re.exactMatch(msg)) {
        QRect scr = QApplication::desktop()->screenGeometry();

        QPoint pt = scr.center();

        if(re.cap(1) == "S") {
            pt.setY(scr.height() - rect().height());
        } else if(re.cap(1) == "N") {
            pt.setY(0);
        } else {
            pt.setY(pt.y() - rect().height()/2);
        }

        if(re.cap(2) == "E") {
            pt.setX(scr.width() - rect().width());
        } else if(re.cap(2) == "O") {
            pt.setX(0);
        } else {
            pt.setX(pt.x() - rect().width()/2);
        }

        move(pt);
        show();
        repaint();
    }
}
