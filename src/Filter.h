/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _FILTER_H_
#define _FILTER_H_

#include <qstring.h>
#include "MtpRegExp.h"
#include "MtpContext.h"

/**
 * 
 * Yann Hodique
 **/
 
class Filter {

public:
    typedef enum {
        Transient,
        Final
    } Policy;

    Filter(QString & name, MtpContext * ctxt = 0);
    virtual ~Filter();

    virtual bool applyTo(QString &) {return false;};
    
    void setPolicy(Policy p);
    Policy policy();

    bool isEnabled();
    void enable();
    void disable();

    QString getName();
    QString getResult();
    void setResult(QString);

    QString applyProcessedRegexpToPattern(MtpRegExp &, const QString &);
    
private:
    QString name;
    QString result;
    Policy pol;
    bool active;
    MtpContext * m_context;
    
};

#endif
