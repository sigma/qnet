/*  Time-stamp: <09/02/2005 20:48:05 Yann Hodique>  */

/**
 *  @file interactiveiodevice.h
 *  @date Wednesday, February 9, 2005
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

#ifndef _INTERACTIVEIODEVICE_H_
#define _INTERACTIVEIODEVICE_H_

#include <QObject>

class InteractiveIODevice : public QObject {

    Q_OBJECT

public:
    InteractiveIODevice(QObject * parent = 0);

    virtual ~InteractiveIODevice();

public slots:
    virtual void sendLogin() = 0;
    virtual void sendPasswd() = 0;

};	// end of class InteractiveIODevice


#endif /* _INTERACTIVEIODEVICE_H_ */
