/*
 *  File: mtpinfo.cpp
 *  Created: Thursday, December 30, 2004
 *  Time-stamp: <30/12/2004 16:44:11 Yann Hodique>
 *  Copyright: Yann Hodique
 *  Email: Yann.Hodique@lifl.fr
 */

/************************************************************************
 *                                                                      *
 * This program is free software; you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 ************************************************************************/

#include "mtpinfo.h"

MtpInfo::MtpInfo(QWidget *parent) : QListWidget(parent) {
    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sp.setHorizontalStretch(0);
    sp.setVerticalStretch(1);
    setSizePolicy(sp);
    setMinimumSize( QSize( 1, 1 ) );
    resize(100,size().height());
}

MtpInfo::~MtpInfo() {}
