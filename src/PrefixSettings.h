/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _PREFIXSETTINGS_H_
#define _PREFIXSETTINGS_H_

#include "prefixsettingsbase.h"

#include <qstring.h>
#include <qmap.h>

/**
 *
 * Yann Hodique
 **/
class PrefixSettings : public PrefixSettingsBase {
    Q_OBJECT

public:

    class PrefixItem {
    public:
        PrefixItem(QString n="") {
            name = n;
        }
        QString name;
    };

    PrefixSettings(QWidget *parent = 0, const char *name = 0);
    ~PrefixSettings();

    QMap<QString,PrefixItem> map;

public slots:
    void addPrefixItem(PrefixItem &);
    void delPrefixItem(const QString&);
    void slotAdd();
    void slotDel();

};

#endif
