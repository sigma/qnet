//
//
// C++ Implementation: $MODULE$
//
// Description:
//
//
// Author: Yann Hodique <Yann.Hodique@lifl.fr>, (C) 2003
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <qregexp.h>

#include "affect.h"

PLUGIN_FACTORY(Affect,"affect")

Affect::Affect(QWidget */*parent*/, const char *name, Master * session) : Page(0, name, session) {}

Affect::~Affect() {}

void Affect::append(const QString& msg) {
    QRegExp re("(\\w+)([\\|\\+]?=)(.*)");
    if(re.exactMatch(msg)) {
        if(re.cap(2) == "=") {
            getMaster()->displayStderr("Setting " + re.cap(1) + " to " + re.cap(3));
            getMaster()->context()->setVar(re.cap(1),re.cap(3));
        }
        else if(re.cap(2) == "+=") {
            getMaster()->context()->setVar(re.cap(1),
                                           getMaster()->context()->getValue(re.cap(1)) + re.cap(3));
        }
        else { // shell command by |=
            getMaster()->displayStderr("Calling shell command : " + re.cap(3));
            getMaster()->context()->setVar(re.cap(1),shellOutput(re.cap(3)));
        }
    }
}

QString Affect::shellOutput(const QString& // cmd
                            ) {
    return QString::null;
}
