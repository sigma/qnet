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
#ifndef FORMAT_H
#define FORMAT_H

#include <page.h>

/**
@author Yann Hodique
*/
class PFormat : public Page {
    Q_OBJECT
public:

    PFormat(QWidget */*parent*/, const char *name, Master * session);
    ~PFormat();

    virtual bool isSlave();
    virtual void append(const QString& msg);

};

#endif
