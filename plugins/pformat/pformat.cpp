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

#include "pformat.h"

PLUGIN_FACTORY(PFormat,"pformat")

PFormat::PFormat(QWidget */*parent*/, const char *name, Master * session) :
Page(0, name, session) {}

PFormat::~PFormat() {}


bool PFormat::isSlave() {
    return false;
}

void PFormat::append(const QString& msg) {
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

