/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "MtpContext.h"


MtpContext::MtpContext() {}


MtpContext::~MtpContext() {}

void MtpContext::setVar(const QString& name, const QString& value) {
    var_map.insert(name,value);
}

void MtpContext::unsetVar(const QString& name) {
    var_map.remove(name);
}

QString MtpContext::getValue(const QString& name) {
    QMap<QString,QString>::Iterator it;
    if ((it = var_map.find(name)) != var_map.end())
        return *it;
    else
        return QString::null;
}
