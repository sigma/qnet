/*  Time-stamp: <10/02/2005 11:38:34 Yann Hodique>  */

/**
 *  @file dispatcher.cpp
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

#include "dispatcher.h"
#include "mtpprotocol.h"
#include "interactionarea.h"
#include "mtpoutput.h"
#include "scm.h"

#include <QStringList>

int Dispatcher::hook_counter = 0;

Dispatcher::Dispatcher(MtpProtocol *p, QObject *parent) : QObject(parent), proto(p), content(this), cursor(&content) {
    connect(p, SIGNAL(readyRead()), this, SLOT(read()));

    append_hook = Scm::getInstance()->createHook(QString("append-hook-%1").arg(hook_counter),1);
    hook_count = hook_counter;
    hook_counter++;
}

Dispatcher::~Dispatcher() {}

void Dispatcher::addInteractionArea(InteractionArea* a) {
    areas.append(a);
    connect(a, SIGNAL(send(const QString&)), this, SLOT(write(const QString&)));
}

void Dispatcher::appendText(const QString& str) {
    QStringList list = str.split('\n',QString::SkipEmptyParts);
    for(QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
        appendLine(*it);
    }
}

void Dispatcher::appendLine(const QString& l) {
    ScmList args;
    args << l;
    Scm::getInstance()->runHook(QString("append-hook-%1").arg(hook_count),args);
    for(AreaList::Iterator it = areas.begin(); it != areas.end(); ++it) {
        (*it)->slotDisplay(l);
    }
    cursor.insertBlock();
    cursor.insertText(l);
}

void Dispatcher::read() {
    while(proto->lineAvailable()) {
        appendLine(proto->readLine());
    }
}

void Dispatcher::write(const QString& txt) {
    proto->writeLine(txt);
}
