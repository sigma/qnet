/*  Time-stamp: <07/02/2005 20:18:02 Yann Hodique>  */

/**
 *  @file mtpbrowser.h
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

#ifndef _MTPBROWSER_H_
#define _MTPBROWSER_H_

#include <QTextBrowser>
#include <QTextCursor>

#include "mtpoutput.h"

/**
 * A graphical MtpOutput, based on a standard QTextBrowser for display
 *
 */
class MtpBrowser : public QTextBrowser, public MtpOutput {

    Q_OBJECT

public:
    /**
     * Constructor
     *
     * @param parent the parent QWidget
     *
     */
    MtpBrowser(QWidget * parent = 0);

    /**
     * Destructor
     *
     */
    ~MtpBrowser();

    /**
     * output a message to the user
     *
     * @param msg message to display
     */
    void display(const QString& msg);

private:
    QTextCursor cursor;
    int block;
};	// end of class MtpBrowser


#endif /* _MTPBROWSER_H_ */
