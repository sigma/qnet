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
#ifndef INTERN_H
#define INTERN_H

#include "page.h"

/**
@author Yann Hodique
*/
class Intern : public Page {
    Q_OBJECT
public:
    Intern(QWidget *parent, const char *name, Master * session);

    ~Intern();

    bool isSlave() {
        return false;
    }
    void append(const QString& msg);

private:
    void affectAppend(const QString&);
    void emitAppend(const QString&);
    void pformatAppend(const QString&);
    void ptimeAppend(const QString&);
    void usersAppend(const QString&);
    void sortAppend(const QString&);
};

#endif
