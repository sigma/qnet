/*
 *  File: dispatcher.cpp
 *  Created: Thursday, December 30, 2004
 *  Time-stamp: <21/01/2005 17:43:52 Yann Hodique>
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

#include "dispatcher.h"
#include "mtpprotocol.h"
#include "interactionarea.h"
#include "mtpoutput.h"

#include <QStringList>

Dispatcher::Dispatcher(MtpProtocol *p, QObject *parent) : QObject(parent), proto(p), content(this), cursor(&content) {
    connect(p, SIGNAL(readyRead()), this, SLOT(read()));
}

Dispatcher::~Dispatcher() {}

void Dispatcher::addInteractionArea(InteractionArea* a) {
    areas.append(a);
    connect(a, SIGNAL(send(const QString&)), proto, SLOT(writeLine(const QString&)));
}

void Dispatcher::appendText(const QString& str) {
    QStringList list = str.split('\n',QString::SkipEmptyParts);
    for(QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
        appendLine(*it);
    }
}

void Dispatcher::appendLine(const QString& l) {
    for(AreaList::Iterator it = areas.begin(); it != areas.end(); ++it) {
        (*it)->display(l);
    }
    cursor.insertBlock();
    cursor.insertText(l);
}

void Dispatcher::read() {
    while(proto->lineAvailable()) {
        appendLine(proto->readLine());
    }
}

void Dispatcher::write(const QString&) {

}
