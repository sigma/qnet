//
//
// C++ Interface: $MODULE$
//
// Description:
//
//
// Author: Yann Hodique <Yann.Hodique@lifl.fr>, (C) 2003
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef EMIT_H
#define EMIT_H

#include <page.h>

/**
@author Yann Hodique
*/
class Emit : public Page {
    Q_OBJECT
public:
    Emit(QWidget *parent, const char *name, Master * session);

    ~Emit();

    virtual bool isSlave();
    virtual void append(const QString&);

};

#endif
