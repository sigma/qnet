/*
 *  File: mtpinfo.h
 *  Created: Thursday, December 30, 2004
 *  Time-stamp: <30/12/2004 15:46:49 Yann Hodique>
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

#ifndef _MTPINFO_H_
#define _MTPINFO_H_

#include <QListWidget>

class MtpInfo : public QListWidget {

    Q_OBJECT

public:
    MtpInfo(QWidget *parent = 0);

    ~MtpInfo();

};	// end of class MtpInfo


#endif /* _MTPINFO_H_ */
