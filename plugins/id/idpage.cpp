/****************************************************************************
** Form implementation generated from reading ui file 'idpage.ui'
**
** Created: Sat Feb 22 12:08:18 2003
**      by: The User Interface Compiler ($Id: idpage.cpp,v 1.1 2003/02/22 15:22:37 Sigma Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "idpage.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qwidgetstack.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qlabel.h>
#include <qregexp.h>

PLUGIN_FACTORY(IdPage,"id");

/*
 *  Constructs a IdPage as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
IdPage::IdPage( QWidget* parent, const char* name, Master * session, WFlags fl )
        : Page( parent, name, session, fl ) {
    if ( !name )
        setName( "IdPage" );
    IdPageLayout = new QGridLayout( this, 1, 1, 11, 6, "IdPageLayout");

    details_button = new QPushButton( this, "details_button" );

    IdPageLayout->addWidget( details_button, 1, 0 );

    update_button = new QPushButton( this, "update_button" );

    IdPageLayout->addWidget( update_button, 1, 2 );

    widgetStack = new QWidgetStack( this, "widgetStack" );

    idform = new IdForm(widgetStack, "idform");
    widgetStack->addWidget(idform, 0);

    browser = new MtpBrowser(widgetStack, "browser");
    widgetStack->addWidget(browser, 1);

    IdPageLayout->addMultiCellWidget( widgetStack, 0, 0, 0, 2 );
    QSpacerItem* spacer = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    IdPageLayout->addItem( spacer, 1, 1 );
    languageChange();
    resize( QSize(445, 308).expandedTo(minimumSizeHint()) );
    
    id = 1;
    switchPage();
    
    connect(details_button, SIGNAL(clicked()), SLOT(switchPage()));
    connect(update_button, SIGNAL(clicked()), SLOT(updatePage()));
    connect(browser,SIGNAL(linkClicked(const QString &)),
	    session, SLOT(slotLinkClicked(const QString &)));
}

/*
 *  Destroys the object and frees any allocated resources
 */
IdPage::~IdPage() {
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void IdPage::languageChange() {
    setCaption( tr( "Form1" ) );
    details_button->setText( tr( "Details" ) );
    update_button->setText( tr( "Update" ) );
}

void IdPage::switchPage() {
    id = 1-id;
    if(id) details_button->setText(tr("Abstract"));
    else details_button->setText(tr("Details"));
    widgetStack->raiseWidget(id);
}

void IdPage::append(QString &msg) {
    browser->append("<font face=fixed>" + msg + "</font>");    
    idform->append(msg);
}

void IdPage::updatePage() {
    QString newmsg("finger " + idform->login_label->text().replace(QRegExp("<[^>]*>"),"").stripWhiteSpace());
    browser->clear();
    getMaster()->send(newmsg);
}
