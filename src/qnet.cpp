/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include <qtextbrowser.h>
#include <qlineedit.h>
#include <qtabwidget.h>
#include <qcombobox.h>
#include <qmessagebox.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qdom.h>
#include <qdir.h>
#include <qlistbox.h>
#include <qwidgetstack.h>
#include <qregexp.h>
#include <qprocess.h>
#include <qradiobutton.h>
#include <qstatusbar.h>

#include <dlfcn.h>

#include "qnet.h"
#include "connectionbox.h"
#include "ChatSession.h"
#include "version.h"
#include "domutil.h"
#include "SessionsDialog.h"
#include "mtpsettings.h"
#include "mtpfilterssettings.h"
#include "UrlSettings.h"
#include "PrefixSettings.h"
#include "fortunesettings.h"
#include "appearancesettings.h"
#include "remotecontrol.h"
#include "page.h"

QMtp::QMtp(QWidget *parent, const char *name)
        : QMtp_base(parent, name), m_document() {

    // kick out this useless status bar
    delete statusBar();

    system_view->setFamily("fixed");
    system_view->setPointSize(10);
    system_view->setWrapPolicy(QTextBrowser::Anywhere);

    connect(tabs,SIGNAL(currentChanged(QWidget*)),
            this, SLOT(slotCurrentPageChanged(QWidget*)));

    //    m_document = new QDomDocument();
    loadConfigFile();
    tabs->setTabPosition((QTabWidget::TabPosition)DomUtil::readIntEntry(m_document,"/appearance/tabs/position",QTabWidget::Top));
    fortune_page = 0;
    fproc = 0;
    //rctl = new RemoteControlServerInfo(this,5000,system_view);

    // plugins
    QStringList plugs = DomUtil::readListEntry(m_document,"/general/plugins","file");
    for(QStringList::Iterator it = plugs.begin(); it != plugs.end(); ++it)
	loadPlugin(*it);
    
    // autoconnect
    QStringList list = DomUtil::readListEntry(m_document,"/general/sessions","session");
    for (QStringList::Iterator it = list.begin(); it != list.end(); ++it)
        if(DomUtil::readBoolEntry(m_document,"/sessions/" + *it + "/autoconnect",false))
            launchSession(*it);
}


QMtp::~QMtp() {
    saveConfigFile();
    //    delete m_document;
}

void QMtp::slotConfigure() {
    MtpSettings settings(this);

    // Select the right widget
    connect(settings.prop_list, SIGNAL(highlighted(int)),
            settings.stack, SLOT(raiseWidget(int)));

    // Filters :
    {
        MtpFiltersSettings * filters_settings = new MtpFiltersSettings(settings.stack);
        settings.stack->addWidget(filters_settings,0);
        settings.prop_list->insertItem("Filters",0);
        filters_settings->setEnabled(false);
    }

    // Urls :
    UrlSettings * url_settings = new UrlSettings(settings.stack);
    settings.stack->addWidget(url_settings,1);
    settings.prop_list->insertItem("Url",1);
    {
        QStringList list = DomUtil::readListEntry(m_document,"/urls/available","type");
        for (QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
            QString name = *it;
            QString motif = DomUtil::readEntry(m_document,"/urls/" + name + "/motif","");
            QString command = DomUtil::readEntry(m_document,"/urls/" + name + "/command","");
            UrlSettings::UrlItem mng(name,motif,command);
            url_settings->addUrlItem(mng);
        }
    }

    // Prefixes :
    PrefixSettings * prefix_settings = new PrefixSettings(settings.stack);
    settings.stack->addWidget(prefix_settings,2);
    settings.prop_list->insertItem("Prefixes",2);
    {
        QStringList list = DomUtil::readListEntry(m_document,"/prefixes","item");
        for (QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
            PrefixSettings::PrefixItem mng(*it);
            prefix_settings->addPrefixItem(mng);
        }
    }

    // Fortune :
    FortuneSettings * fortune_settings = new FortuneSettings(settings.stack);
    settings.stack->addWidget(fortune_settings,3);
    settings.prop_list->insertItem("Fortune",3);
    {
        QString args = DomUtil::readEntry(m_document,"/fortune");
        fortune_settings->fortune_edit->setText(args);
    }

    // Appearance :
    AppearanceSettings * appearance_settings = new AppearanceSettings(settings.stack);
    settings.stack->addWidget(appearance_settings,4);
    settings.prop_list->insertItem("Appearance",4);
    {
        int position = DomUtil::readIntEntry(m_document,"/appearance/tabs/position",QTabWidget::Top);
        appearance_settings->rbTop->setChecked(position==QTabWidget::Top);
        appearance_settings->rbBottom->setChecked(!appearance_settings->rbTop->isChecked());
    }

    if (settings.exec()) {

        // Filters

        // Urls
        {
            QStringList l;
            for (uint i=0; i< url_settings->urls_box->count(); i++)
                l << url_settings->urls_box->text(i);
            DomUtil::writeListEntry(m_document,"/urls/available","type",l);

            for (uint i=0; i< url_settings->urls_box->count(); i++) {
                UrlSettings::UrlItem it = *(url_settings->map.find(url_settings->urls_box->text(i)));
                DomUtil::writeEntry(m_document,"/urls/" + it.name + "/motif",it.prefix);
                DomUtil::writeEntry(m_document,"/urls/" + it.name + "/command",it.command);
            }
        }

        // Prefixes
        {
            QStringList l;
            for (uint i=0; i< prefix_settings->prefix_box->count(); i++)
                l << prefix_settings->prefix_box->text(i);
            DomUtil::writeListEntry(m_document,"/prefixes","item",l);
        }

        // Fortune :
        {
            DomUtil::writeEntry(m_document,"/fortune",fortune_settings->fortune_edit->text());
        }

        // Appearance :
        {
            int position = appearance_settings->rbTop->isChecked()?QTabWidget::Top : QTabWidget::Bottom;
            DomUtil::writeIntEntry(m_document,"appearance/tabs/position",position);
            tabs->setTabPosition((QTabWidget::TabPosition)position);
        }


    }
}

void QMtp::fileNew() {
    ConnectionBox box;
    QStringList list = DomUtil::readListEntry(m_document,"/general/sessions","session");
    for (QStringList::Iterator it = list.begin(); it != list.end(); ++it)
        box.session_box->insertItem(*it);
    box.session_box->setFocus();

    if(box.exec() && (box.session_box->currentText() != "")) {
        launchSession(box.session_box->currentText());
    }
}

Page * QMtp::getNewPage(QString type,QString name,ChatSession * ref) {
/*    if (type == "tell") {
            TellPage * edit = new TellPage(tabs,name,ref);
            edit->setPrefix("tell " + name + " ");
            tabs->addTab(edit,name);
            tabs->showPage(edit);
            tab_map.insert(edit,ref);


            connect(edit, SIGNAL(textDisplayed(QWidget *)),
                    this, SLOT(slotTextDisplayed(QWidget *)));

            return edit;
        }
    else if (type == "browser") {
            BrowserPage * edit = new BrowserPage(tabs,name,ref);
            tabs->addTab(edit,name);
            tabs->showPage(edit);
            tab_map.insert(edit,ref);

            connect(edit, SIGNAL(textDisplayed(QWidget *)),
                    this, SLOT(slotTextDisplayed(QWidget *)));

            return edit;
        }
    else if (type == "drawing") {
            Painter * paint = new Painter(tabs,name,ref);
            tabs->addTab(paint,name);
            tabs->showPage(paint);
            tab_map.insert(paint,ref);

            return paint;
        }
    else if (type == "splash") {
            Splash * splash = new Splash(tabs,name,ref);
            tab_map.insert(splash,ref);

            return splash;
        }*/
    QMap<QString,void*>::Iterator it;
    if((it = plugins_map.find(type)) != plugins_map.end()) {
	create_t* create_plugin = (create_t*) dlsym(*it, "create");
	Page* page = create_plugin(tabs,name,ref);
	if (page->isSlave()) {
	    tabs->addTab(page,name);
            tabs->showPage(page);
	}
	tab_map.insert(page,ref);
	connect(page, SIGNAL(textDisplayed(QWidget *)),
		this, SLOT(slotTextDisplayed(QWidget *)));
	return page;
    }
    system_view->append("No type \"" + type + "\" available\n");
    return 0;
}

void QMtp::fileSessions() {
    SessionsDialog dlg;

    QStringList list = DomUtil::readListEntry(m_document,"/general/sessions","session");
    for (QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
        QString name = *it;
        QString host = DomUtil::readEntry(m_document,"/sessions/" + name + "/host","");
        QString port = DomUtil::readEntry(m_document,"/sessions/" + name + "/port","");
        QString login = DomUtil::readEntry(m_document,"/sessions/" + name + "/login","");
        QString password = DomUtil::readEntry(m_document,"/sessions/" + name + "/password","");
        bool autoconnect = DomUtil::readBoolEntry(m_document,"/sessions/" + name + "/autoconnect",false);
        SessionsDialog::SessionItem session(name,host,port,login,password,autoconnect);
        dlg.addSessionItem(session);
    }

    if (dlg.exec()) {
        QStringList l;
        for (uint i=0; i< dlg.sessions_box->count(); i++)
            l << dlg.sessions_box->text(i);
        DomUtil::writeListEntry(m_document,"/general/sessions","session",l);

        for (uint i=0; i< dlg.sessions_box->count(); i++) {
            SessionsDialog::SessionItem it = *(dlg.map.find(dlg.sessions_box->text(i)));
            DomUtil::writeEntry(m_document,"/sessions/" + it.name + "/host",it.host);
            DomUtil::writeEntry(m_document,"/sessions/" + it.name + "/port",it.port);
            DomUtil::writeEntry(m_document,"/sessions/" + it.name + "/login",it.login);
            DomUtil::writeEntry(m_document,"/sessions/" + it.name + "/password",it.password);
            DomUtil::writeBoolEntry(m_document,"/sessions/" + it.name + "/autoconnect",it.autoconnect);
        }
    }
}

void QMtp::closeCurrentTab() {
    closeTab(tabs->currentPage());
}

void QMtp::closeTab(QWidget *w) {
    if(w == fortune_page) {
        delete w;
        fortune_page = 0;
        return;
    }
    if(w != tab) {
        tabs->removePage(w);
        QMap<QWidget*,ChatSession*>::Iterator it;
        if ((it = tab_map.find(w)) != tab_map.end()) {
            (*it)->kill((Page*)w);
        } else // session tab
            sessions.remove((ChatSession*)w);
        delete w;
    }
}

void QMtp::fileExit() {
    saveConfigFile();
    close();
}

void QMtp::gotoNextTab() {
    tabs->setCurrentPage((tabs->currentPageIndex() + 1) % tabs->count());
}

void QMtp::gotoPreviousTab() {
    tabs->setCurrentPage((tabs->currentPageIndex() + tabs->count() - 1) % tabs->count());
}

void QMtp::helpAbout() {
    QMessageBox::about(this, "About QNet", CLIENT + QString("\n© 2002 - Sigma <Yann.Hodique@lifl.fr>"));
}

bool QMtp::loadConfigFile() {
    QFile fin(QDir::homeDirPath() + "/.qnetrc");
    if (!fin.open(IO_ReadOnly)) {
        QMessageBox::critical(this,"Error","Could not read config file");
        return false;
    }

    int errorLine, errorCol;
    QString errorMsg;
    if (!m_document.setContent(&fin, &errorMsg, &errorLine, &errorCol)) {
        QMessageBox::critical(this,"Error",QString("This is not a valid config file.\nXML error in line %1, column %2:\n%3").arg(errorLine).arg(errorCol).arg(errorMsg));
        fin.close();
        return false;
    }
    if (m_document.documentElement().nodeName() !="qnet") {
        QMessageBox::critical(this,"Error","This is not a valid config file.");
        fin.close();
        return false;
    }

    fin.close();

    return true;
}

bool QMtp::saveConfigFile() {
    QFile fout(QDir::homeDirPath() + "/.qnetrc");
    if( !fout.open(IO_WriteOnly) ) {
        QMessageBox::critical(this,"Error","Could not write the config file.");
        return false;
    }

    QTextStream stream(&fout);
    stream << m_document.toString();
    fout.close();

    return true;
}

void QMtp::slotTextDisplayed(QWidget* w) {
    QString current_label = tabs->label(tabs->indexOf(w));
    if ((tabs->currentPage() == w) || current_label.endsWith("*"))
        return;
    tabs->setTabLabel(w,current_label + "*");
}

void QMtp::slotCurrentPageChanged(QWidget* w) {
    QString current_label = tabs->label(tabs->indexOf(w));
    if (current_label.endsWith("*"))
        tabs->setTabLabel(w,current_label.replace(QRegExp("\\*$"),""));
}

void QMtp::slotDisplayFortune() {
    if (fproc)
        return;
    fproc = new QProcess(this);
    if (!(this->fortune_page)) {
        fortune_page = new QTextBrowser(tabs,"Fortune");
        fortune_page->setTextFormat(Qt::RichText);

        fortune_page->setWrapPolicy(QTextBrowser::Anywhere);

        tabs->addTab(fortune_page,"Fortune");
        tabs->showPage(fortune_page);
    }

    QStringList list;
    QStringList list_args = QStringList::split(" ",DomUtil::readEntry(m_document,"/fortune"));
    list << "fortune";

    for (QStringList::Iterator it = list_args.begin(); it != list_args.end(); ++it)
        list << (*it);

    connect(fproc,SIGNAL(readyReadStdout()),
            this, SLOT(readFortune()));
    connect(fproc,SIGNAL(processExited()),
            this, SLOT(endFortune()));
    fproc->setArguments(list);
    fproc->start();
}

void QMtp::readFortune() {
    QProcess *p = (QProcess*) sender();
    while (p->canReadLineStdout()) {
        QString msg(p->readLineStdout());
        fortune_page->append(msg);
    }
}

void QMtp::endFortune() {
    fortune_page->append("<hr>");
    delete fproc;
    fproc = 0;
}

void QMtp::loadPlugin(const QString& file_name) {
    system_view->append("Loading " + file_name);
    
    void* plug = dlopen(file_name, RTLD_LAZY);
    if (!plug) {
        system_view->append(QString("Cannot load library: ") + dlerror() + "\n");
        return;
    }

    create_t* create_plugin = (create_t*) dlsym(plug, "create");
    destroy_t* destroy_plugin = (destroy_t*) dlsym(plug, "destroy");
    name_t* name_plugin = (name_t*) dlsym(plug, "name");
    if (!create_plugin || !destroy_plugin || !name_plugin) {
        system_view->append(QString("Cannot load symbols: ") + dlerror() + "\n");
	return;
    }
    
    plugins_map.insert(name_plugin(),plug);
}

void QMtp::launchSession(QString name) {
    ChatSession * session = new ChatSession(name,this,tabs,0,&m_document);

    sessions.push_back(session);

    tabs->addTab(session,name);
    tabs->showPage(session);

    connect(session, SIGNAL(textDisplayed(QWidget *)),
            this, SLOT(slotTextDisplayed(QWidget *)));
}
