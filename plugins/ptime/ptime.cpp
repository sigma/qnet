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

#include <iostream>

#include <qdatetime.h>
#include <qregexp.h>

#include "ptime.h"

PLUGIN_FACTORY(PTime,"ptime");

PTime::PTime(QWidget */*parent*/, const char *name, Master * session) :
Page(0, name, session) {}

PTime::~PTime() {}


bool PTime::isSlave() {
    return false;
}

void PTime::append(const QString& msg) {
    QRegExp re("(\\w+)<-\\[(date|time)\\](.*)");
    if(re.exactMatch(msg)) {
        if(re.cap(2) == "time") {
            getMaster()->context()->setVar(re.cap(1),QTime::currentTime().toString(re.cap(3)));
//            getMaster()->displayStderr("Setting " + re.cap(1) + " to " + QTime::currentTime().toString(re.cap(3)));
        }
        else {// date
            getMaster()->context()->setVar(re.cap(1),QDate::currentDate().toString(re.cap(3)));
//            getMaster()->displayStderr("Setting " + re.cap(1) + " to " + QDate::currentDate().toString(re.cap(3)));
        }
    }
}

