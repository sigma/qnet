/****************************************************************************
** mainwin.cpp - the main window.  holds contactlist and buttons.
** Copyright (C) 2001, 2002  Justin Karneges
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,USA.
**
****************************************************************************/

#include"mainwin.h"

#include<qmessagebox.h>
#include<qiconset.h>
#include<qtooltip.h>
#include<qstyle.h>
#include<qapplication.h>
#include<qptrlist.h>
#include<qtimer.h>
#include<qobjectlist.h>

#include "qnet.h"
#include "version.h"

// deletes submenus in a popupmenu
void qpopupmenuclear(QPopupMenu *p) {
    while(p->count()) {
        QMenuItem *item = p->findItem(p->idAt(0));
        QPopupMenu *popup = item->popup();
        p->removeItemAt(0);

        if(popup)
            delete popup;
    }
}


//*******************************************************
//  MainWin
//*******************************************************
MainWin::MainWin(bool _onTop, bool _asTool, const char *name)
        :QWidget(0, name, 0 | (_onTop ? WStyle_StaysOnTop: 0) | (_asTool ? WStyle_Tool: 0)) {
    tray = 0;
    trayMenu = 0;

    mw = new QMtp();
    mw->setCaption( CLIENT );

    mw->show();
    connect(mw, SIGNAL(closeProgram()), SLOT(tryCloseProgram()));
    
    icon_path = mw->iconPath();
}

MainWin::~MainWin() {
    if(tray) {
        delete tray;
        tray = 0;
        delete trayMenu;
        trayMenu = 0;
    }
}

void MainWin::setUseDock() {

    if(tray || (icon_path.isNull())) {
	return;
    }

    trayMenu = new QPopupMenu;
    connect(trayMenu, SIGNAL(aboutToShow()), SLOT(buildTrayMenu()));

    QImage im(icon_path);
    tray = new MTray(im, "QNet", trayMenu);
    connect(tray, SIGNAL(clicked(const QPoint &, int)), SLOT(trayClicked(const QPoint &, int)));
    connect(tray, SIGNAL(doubleClicked(const QPoint &)), SLOT(trayDoubleClicked()));
    connect(tray, SIGNAL(closed()), SIGNAL(closeProgram()));

    tray->show();
}


void MainWin::buildTrayMenu() {
    if(!trayMenu)
        return;
    trayMenu->clear();

    if(mw->isHidden())
        trayMenu->insertItem(tr("Un&hide"), this, SLOT(trayShow()));
    else
        trayMenu->insertItem(tr("&Hide"), this, SLOT(trayHide()));

    trayMenu->insertSeparator();
    trayMenu->insertItem(tr("&Quit"), this, SLOT(tryCloseProgram()));
}




void MainWin::trayClicked(const QPoint &, int button) {
    if(button == MidButton) {
        return;
    }

    if(mw->isHidden())
        trayShow();
    else
        trayHide();
}

void MainWin::trayDoubleClicked() {
    if(isHidden())
        trayShow();
    else
        trayHide();
}

void MainWin::trayShow() {
    mw->show();
}

void MainWin::trayHide() {
    mw->hide();
}

void MainWin::tryCloseProgram()
{
    closeProgram();
}

//----------------------------------------------------------------------------
// MTray
//----------------------------------------------------------------------------
MTray::MTray(const QImage &icon, const QString &tip, QPopupMenu *popup, QObject *parent)
:QObject(parent) {
    ti = new TrayIcon(makeIcon(icon), tip, popup);
    connect(ti, SIGNAL(clicked(const QPoint &, int)), SIGNAL(clicked(const QPoint &, int)));
    connect(ti, SIGNAL(doubleClicked(const QPoint &)), SIGNAL(doubleClicked(const QPoint &)));
    connect(ti, SIGNAL(closed()), SIGNAL(closed()));
    ti->show();
}

MTray::~MTray() {
    delete ti;
}

void MTray::setToolTip(const QString &str) {
    ti->setToolTip(str);
}

void MTray::setImage(const QImage &i) {
    ti->setIcon(makeIcon(i));
}

void MTray::show() {
    ti->show();
}

void MTray::hide() {
    ti->hide();
}

QPixmap MTray::makeIcon(const QImage &_in) {
#ifdef Q_WS_X11

    // on X11, the KDE dock is 22x22.  let's make our icon "seem" bigger.
    QImage real(22,22,32);
    //QImage in = _in.convertToImage();
    QImage in = _in;
    in.detach();
    real.fill(0);
    real.setAlphaBuffer(true);

    // make sure it is no bigger than 16x16
    if(in.width() > 16 || in.height() > 16)
        in = in.smoothScale(16,16);

    int xo = (real.width() - in.width()) / 2;
    int yo = (real.height() - in.height()) / 2;

    int n, n2;

    // draw a border
    /*for(n = 0; n < 22; ++n) {
    	real.setPixel(n,  0, qRgb(0x80,0x80,0x80));
    	real.setPixel(n, 21, qRgb(0x00,0x00,0x00));
    	real.setPixel( 0, n, qRgb(0x80,0x80,0x80));
    	real.setPixel(21, n, qRgb(0x00,0x00,0x00));
    }*/

    // draw a dropshadow
    for(n2 = 0; n2 < in.height(); ++n2) {
        for(n = 0; n < in.width(); ++n) {
            if(qAlpha(in.pixel(n,n2))) {
                int x = n + xo + 2;
                int y = n2 + yo + 2;
                real.setPixel(x, y, qRgba(0x80,0x80,0x80,0xff));
            }
        }
    }
    // draw the image
    for(n2 = 0; n2 < in.height(); ++n2) {
        for(n = 0; n < in.width(); ++n) {
            if(qAlpha(in.pixel(n,n2))) {
                QRgb c = in.pixel(n, n2);
                real.setPixel(n + xo, n2 + yo, qRgba(qRed(c), qGreen(c), qBlue(c), 0xff));
            }
        }
    }
    // create the alpha layer
    for(n2 = real.height()-2; n2 >= 0; --n2) {
        for(n = 0; n < real.width(); ++n) {
            uint c = real.pixel(n, n2);
            if(c > 0) {
                QRgb old = real.pixel(n, n2);
                real.setPixel(n, n2, qRgba(qRed(old), qGreen(old), qBlue(old), 0xff));
            }
        }
    }

    QPixmap icon;
    icon.convertFromImage(real);
    return icon;
    //}
#else

    QPixmap icon;
    icon.convertFromImage(_in);
    return icon;
#endif
}
