/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _ITEMFILTER_H_
#define _ITEMFILTER_H_

#include "Filter.h"

/**
 *
 * Yann Hodique
 **/
class ItemFilter : public Filter {

public:
    ItemFilter(const QString & name, MtpContext * ctxt = 0);
    ~ItemFilter();

    void setRegExp(const QString& reg);
    void setResultPattern(const QString& pat);
    bool applyTo(QString &);

    QString getRegExp() const;
    QString getResultPattern() const;

private:
    MtpRegExp reg;
    QString pattern,reg_exp;
    MtpContext * m_context;
};

#endif
