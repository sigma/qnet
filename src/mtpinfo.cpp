/*  Time-stamp: <07/02/2005 21:22:37 Yann Hodique>  */

/**
 *  @file mtpinfo.cpp
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

#include "mtpinfo.h"

MtpInfo::MtpInfo(QWidget *parent) : QListWidget(parent) {
    setFixedWidth(100);
}

MtpInfo::~MtpInfo() {}
