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
#include "emit.h"

PLUGIN_FACTORY(Emit,"emit");

Emit::Emit(QWidget */*parent*/, const char *name, Master * session) :
Page(0, name, session) {}


Emit::~Emit() {}


bool Emit::isSlave() {
    return false;
}

void Emit::append(const QString& msg) {
    getMaster()->send(msg);
}

