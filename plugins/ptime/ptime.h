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
#ifndef TIME_H
#define TIME_H

#include <page.h>

/**
@author Yann Hodique
*/
class PTime : public Page {
    Q_OBJECT
public:

    PTime(QWidget */*parent*/, const char *name, Master * session);
    ~PTime();

    virtual bool isSlave();
    virtual void append(const QString& msg);

};

#endif
