/*
 *  File: mtpbrowser.h
 *  Created: Thursday, December 30, 2004
 *  Time-stamp: <02/01/2005 11:57:56 Yann Hodique>
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

#ifndef _MTPBROWSER_H_
#define _MTPBROWSER_H_

#include <QTextBrowser>
#include <QTextCursor>

#include "mtpoutput.h"

class MtpBrowser : public QTextBrowser, public MtpOutput {

    Q_OBJECT

public:
    MtpBrowser(QWidget * parent = 0);

    ~MtpBrowser();

    void display(const QString&);

private:
    QTextCursor cursor;
    int block;
};	// end of class MtpBrowser


#endif /* _MTPBROWSER_H_ */
