/*
 *  File: dispatcher.h
 *  Created: Thursday, December 30, 2004
 *  Time-stamp: <30/12/2004 18:25:46 Yann Hodique>
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

class Dispatcher : public QObject {

    Q_OBJECT

public:
    Dispatcher(MtpProtocol * p, QObject *parent = 0);
    ~Dispatcher();

public slots:
    void addInteractionArea(InteractionArea*);
    void appendText(const QString&);

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
