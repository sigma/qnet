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
#include <qdatetime.h>

#include "intern.h"

PLUGIN_FACTORY(Intern,"intern")

Intern::Intern(QWidget */*parent*/, const char *name, Master * session) : Page(0, name, session) {}

Intern::~Intern() {}

void Intern::append(const QString& msg) {
    QRegExp re("(affect|emit|pformat|ptime|users):(.*)");
    if(re.exactMatch(msg)) {
        if(re.cap(1) == "affect")
            affectAppend(re.cap(2));
        else if(re.cap(1) == "emit")
            emitAppend(re.cap(2));
        else if(re.cap(1) == "pformat")
            pformatAppend(re.cap(2));
        else if(re.cap(1) == "ptime")
            ptimeAppend(re.cap(2));
        else if(re.cap(1) == "users")
            usersAppend(re.cap(2));
    }
}

void Intern::affectAppend(const QString& msg) {
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
    }
}

void Intern::emitAppend(const QString& msg) {
    getMaster()->send(msg);
}

void Intern::pformatAppend(const QString& msg) {
    QRegExp re("(\\w+)<-\"(.*)\"((,\\(\".*\":-?\\d+\\))*)");
    QRegExp re2("\\(\"(.*)\":(-?\\d+)\\)");
    if(re.exactMatch(msg)) {
        QString value(re.cap(2));
        QStringList args = QStringList::split(',',re.cap(3));
        for(QStringList::Iterator it = args.begin(); it != args.end(); ++it) {
            if(re2.exactMatch(*it))
                value = value.arg(re2.cap(1),re2.cap(2).toInt());
        }
        getMaster()->context()->setVar(re.cap(1),value);
//        getMaster()->displayStderr("Setting " + re.cap(1) + " to " + value);
    }
}

void Intern::ptimeAppend(const QString& msg) {
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

void Intern::usersAppend(const QString& msg) {
    QRegExp re("(add|remove):(\\w+)");
    if(re.exactMatch(msg)) {
        if(re.cap(1) == "add")
            getMaster()->incoming(re.cap(2));
        else
            getMaster()->outgoing(re.cap(2));
    }
}
