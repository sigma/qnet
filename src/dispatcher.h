/*
 *  File: dispatcher.h
 *  Created: Thursday, December 30, 2004
 *  Time-stamp: <21/01/2005 16:16:25 Yann Hodique>
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

#ifndef _DISPATCHER_H_
#define _DISPATCHER_H_

#include <QTextDocument>
#include <QTextCursor>
#include <QList>

class InteractionArea;
class MtpProtocol;

/**
 * Interface between a MtpProtocol and some InteractionArea
 *
 * @todo suppress direct dependency to MtpProtocol, and replace it with some
 * Protocol interface
 *
 */
class Dispatcher : public QObject {

    Q_OBJECT

public:
    /**
     * Constructor
     *
     * @param p the MtpProtocol to which this Dispatcher is attached
     * @param parent the parent QObject
     *
     */
    Dispatcher(MtpProtocol * p, QObject *parent = 0);

    /**
     * Destructor
     *
     */
    ~Dispatcher();

public slots:
    /**
     * add a new InteractionArea to this Dispatcher. This provides multiple
     * views over the same MtpProtocol object.
     *
     * @param area the area to link
     *
     */
    void addInteractionArea(InteractionArea* area);

    /**
     * append a text to the output of each InteractionArea linked to the
     * MtpProtocol
     *
     * @param txt the text to append
     */
    void appendText(const QString& txt);

private:
    void appendLine(const QString&);

    typedef QList<InteractionArea*> AreaList;
    MtpProtocol * proto;
    QTextDocument content;
    QTextCursor cursor;
    AreaList areas;

private slots:
    void read();
    void write(const QString&);
};	// end of class Dispatcher


#endif /* _DISPATCHER_H_ */
