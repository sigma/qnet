/*
 *  File: interactionarea.h
 *  Created: Thursday, December 30, 2004
 *  Time-stamp: <21/01/2005 16:57:55 Yann Hodique>
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

/**
 * Interface for describing interaction between a user and a service
 *
 */
class InteractionArea : public QObject {

    Q_OBJECT

public:
    /**
     * Constructor
     *
     * @param parent the parent QObject
     *
     */
    InteractionArea(QObject *parent = 0);

    /**
     * Destructor
     *
     */
    virtual ~InteractionArea();

protected:
    /**
     * the output device
     *
     * @return where to output things
     */
    virtual MtpOutput * getOutput() = 0;

    /**
     * the input device
     *
     * @return from where to read things
     */
    virtual MtpInput * getInput() = 0;

public slots:
    /**
     * display a message on the output
     *
     * @param msg message to display
     */
    virtual void display(const QString& msg);

signals:
    /**
     * signal emitted when a user wants to send a message
     *
     * @param msg the message to send
     *
     */
    void send(const QString& msg);
};	// end of class InteractionArea


#endif /* _INTERACTIONAREA_H_ */
