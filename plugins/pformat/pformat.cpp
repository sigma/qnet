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

#include "pformat.h"

PLUGIN_FACTORY(PFormat,"pformat");

PFormat::PFormat(QWidget */*parent*/, const char *name, Master * session) :
Page(0, name, session) {}

PFormat::~PFormat() {}


bool PFormat::isSlave() {
    return false;
}

void PFormat::append(const QString& msg) {}

