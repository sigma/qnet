/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _MTPCONTEXT_H_
#define _MTPCONTEXT_H_

#include <qmap.h>

/**
 * 
 * Yann Hodique
 **/
class MtpContext {

public:
    MtpContext();
    ~MtpContext();
    void setVar(QString name, QString value);
    void unsetVar(QString name);
    QString getValue(QString name);

private:
    QMap<QString,QString> var_map;
};

#endif
