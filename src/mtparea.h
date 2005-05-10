/*  Time-stamp: <08/02/2005 09:21:28 Yann Hodique>  */

/**
 *  @file mtparea.h
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

#ifndef _MTPAREA_H_
#define _MTPAREA_H_

#include "interactionarea.h"
#include "mtpbrowser.h"

#include <QStringList>
#include <QWidget>

class MtpInfo;
class MtpEdit;
class MtpBrowser;
class QBoxLayout;
class QResizeEvent;
class QAction;
class QSplitter;

class MtpArea : public InteractionArea, public QWidget {
    Q_OBJECT
public:
    MtpArea(QWidget *parent = 0);

    ~MtpArea();

    MtpOutput * getOutput() const;
    MtpInput * getInput() const;

public slots:
    virtual void returnPressed();
    void toggleUserBox();

protected:
    MtpEdit* chat_edit;
    MtpInfo* users_box;
    MtpBrowser* chat_view;

    QBoxLayout* chatpage_layout;

    void resizeEvent(QResizeEvent*);

private:
    QAction *return_pressed;
    bool user_box_visible;
    QSplitter *vsplit, *hsplit;
};	// end of class MtpArea


#endif /* _MTPAREA_H_ */