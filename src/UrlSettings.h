/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _URLSETTINGS_H_
#define _URLSETTINGS_H_

#include "urlsettingsbase.h"

#include <qwidget.h>
#include <qstring.h>
#include <qmap.h>

/**
 * 
 * Yann Hodique
 **/
class UrlSettings : public UrlSettingsBase
{
  Q_OBJECT

public:

	class UrlItem {
        public:
        UrlItem(QString n="", QString p="", QString c="") {name = n; prefix = p; command = c;} 
        QString name;
        QString prefix;
        QString command;
        };

  UrlSettings(QWidget *parent = 0, const char *name = 0);
  ~UrlSettings();

  	QMap<QString,UrlItem> map;
    
public slots:
  void addUrlItem(UrlItem &);
  void delUrlItem(QString);
  void slotAdd();
  void slotDel();
  void slotUpdateInfo(const QString &);

};

#endif
