/****************************************************************************
** Form interface generated from reading ui file 'idpage.ui'
**
** Created: Sat Feb 22 12:08:09 2003
**      by: The User Interface Compiler ($Id: idpage.h,v 1.1 2003/02/22 15:22:37 Sigma Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef IDPAGE_H
#define IDPAGE_H

#include <qvariant.h>
#include <qwidget.h>

#include "page.h"
#include "master.h"
#include "idform.h"
#include "mtpbrowser.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QPushButton;
class QWidgetStack;

class IdPage : public Page
{
    Q_OBJECT

public:
    IdPage( QWidget* parent, const char* name, Master * session, WFlags fl = 0 );
    ~IdPage();

    QPushButton* details_button;
    QPushButton* update_button;
    QWidgetStack* widgetStack;
    
    IdForm* idform;
    MtpBrowser* browser;

private slots:
    void switchPage();
    void append(QString&);
    void updatePage();
    
protected:
    QGridLayout* IdPageLayout;

protected slots:
    virtual void languageChange();

private:
int id;
};

#endif // IDPAGE_H
