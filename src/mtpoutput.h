/*  Time-stamp: <07/02/2005 20:18:03 Yann Hodique>  */

/**
 *  @file mtpoutput.h
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

#ifndef _MTPOUTPUT_H_
#define _MTPOUTPUT_H_

/**
 * Interface class for output to a user
 *
 */
class MtpOutput {
public:
    /**
     * Constructor
     *
     */
    MtpOutput() {}

    /**
     * Destructor
     *
     */
    virtual ~MtpOutput() {};

    /**
     * display a message to the user
     *
     * @param msg message to display
     */
    virtual void display(const QString& msg) = 0;

};	// end of class MtpOutput


#endif /* _MTPOUTPUT_H_ */
