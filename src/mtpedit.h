/*  Time-stamp: <08/02/2005 09:24:20 Yann Hodique>  */

/**
 *  @file mtpedit.h
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

#ifndef _MTPEDIT_H_
#define _MTPEDIT_H_

#include <QTextEdit>
#include <QResizeEvent>

#include "mtpinput.h"

/**
 * A graphical MtpInput based on a standard QTextEdit
 *
 * @todo make the "return" action customizable
 */
class MtpEdit : public QTextEdit, public MtpInput {

    Q_OBJECT

public:
    /**
     * Constructor
     *
     * @param parent the parent QWidget
     *
     */
    MtpEdit(QWidget *parent = 0);

    /**
     * Destructor
     *
     */
    ~MtpEdit();

public slots:
    /**
     * action to perform for sending
     *
     * @todo change the name
     *
     */
    void returnPressedSlot();

private:
    QShortcut* return_pressed;

signals:
    /**
     * emitted when a message is to be sent
     *
     */
    void send(const QString&);
};	// end of class MtpEdit


#endif /* _MTPEDIT_H_ */