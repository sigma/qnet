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
#ifndef AFFECT_H
#define AFFECT_H

#include "page.h"

/**
@author Yann Hodique
*/
class Affect : public Page {
    Q_OBJECT
public:
    Affect(QWidget *parent, const char *name, Master * session);

    ~Affect();

    bool isSlave() {
        return false;
    }
    void append(QString& arg1);

};

#endif
