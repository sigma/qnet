/*  Time-stamp: <07/02/2005 20:18:03 Yann Hodique>  */

/**
 *  @file mtpinput.h
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

#ifndef _MTPINPUT_H_
#define _MTPINPUT_H_

/**
 * Interface class for input from a user
 *
 * @todo think about common specific actions
 *
 */
class MtpInput {

public:
    /**
     * Constructor
     *
     */
    MtpInput() {}

    /**
     * Destructor
     *
     */
    virtual ~MtpInput() {}

};	// end of class MtpInput


#endif /* _MTPINPUT_H_ */
