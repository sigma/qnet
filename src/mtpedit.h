/*
 *  File: mtpedit.h
 *  Created: Thursday, December 30, 2004
 *  Time-stamp: <30/12/2004 17:49:23 Yann Hodique>
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

#ifndef _MTPEDIT_H_
#define _MTPEDIT_H_

#include <QTextEdit>
#include <QResizeEvent>

#include "mtpinput.h"

class QShortcut;

class MtpEdit : public QTextEdit, public MtpInput {

    Q_OBJECT

public:
    MtpEdit(QWidget *parent = 0);

    ~MtpEdit();

public slots:
    void returnPressedSlot();

private:
    QShortcut* return_pressed;

signals:
    void send(const QString&);
};	// end of class MtpEdit


#endif /* _MTPEDIT_H_ */
