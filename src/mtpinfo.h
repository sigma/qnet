/*  Time-stamp: <07/02/2005 20:18:02 Yann Hodique>  */

/**
 *  @file mtpinfo.h
 *  @date Thursday, December 30, 2004
 *  @author Yann Hodique <Yann.Hodique@lifl.fr>
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
