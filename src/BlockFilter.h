/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _BLOCKFILTER_H_
#define _BLOCKFILTER_H_

#include <qregexp.h>

#include "Filter.h"
#include "InputFilter.h"

/**
 * 
 * Yann Hodique
 **/
class BlockFilter : public Filter {

public:

    typedef enum {
        BEGIN,
        IN
    } Position;

    BlockFilter(QString & name, MtpContext * ctxt);
    ~BlockFilter();

    void setInputDependency(InputFilter *);
    InputFilter * getInputDependency();

    void setBeginRegExp(QString reg);
    void setEndRegExp(QString reg);
    void setResultPattern(QString pat);
    
    bool applyTo(QString &, Position pos = IN);
    bool isFinished();

    
private:
    InputFilter * dependency;
    bool finished;
    MtpRegExp beg_reg,end_reg;
    MtpContext * m_context;
    QString pattern;
};

#endif
