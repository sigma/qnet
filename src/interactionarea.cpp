/*
 *  File: interactionarea.cpp
 *  Created: Thursday, December 30, 2004
 *  Time-stamp: <30/12/2004 11:12:45 Yann Hodique>
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

#include "interactionarea.h"
#include "mtpoutput.h"

InteractionArea::InteractionArea(QObject *parent) : QObject(parent) {}

InteractionArea::~InteractionArea() {}

void InteractionArea::display(const QString& str) {
    MtpOutput * out = getOutput();
    if(out)
        out->display(str);
}
