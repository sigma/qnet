/*
 *  File: interactionarea.h
 *  Created: Thursday, December 30, 2004
 *  Time-stamp: <30/12/2004 12:43:40 Yann Hodique>
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

#ifndef _INTERACTIONAREA_H_
#define _INTERACTIONAREA_H_

#include <QObject>

class MtpOutput;
class MtpInput;

class InteractionArea : public QObject {

    Q_OBJECT

public:
    InteractionArea(QObject *parent = 0);

    virtual ~InteractionArea();

    virtual MtpOutput * getOutput() = 0;
    virtual MtpInput * getInput() = 0;

public slots:
    virtual void display(const QString&);

signals:
    void send(const QString&);
};	// end of class InteractionArea


#endif /* _INTERACTIONAREA_H_ */
