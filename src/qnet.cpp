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
#include <qlistbox.h>
#include <qwidgetstack.h>
#include <qregexp.h>
#include <qprocess.h>
#include <qradiobutton.h>
#include <qstatusbar.h>
#include <qaction.h>
#include <qpopupmenu.h>
#include <qfiledialog.h>
#include <qfontdatabase.h>

#include <dlfcn.h>

#include "qnet.h"
#include "connectionbox.h"
#include "ChatSession.h"
#include "version.h"
#include "domutil.h"
#include "mtpsettings.h"
#include "mtpfilterssettings.h"
#include "UrlSettings.h"
#include "PrefixSettings.h"
#include "fortunesettings.h"
#include "appearancesettings.h"
#include "remotecontrol.h"
#include "page.h"
#include "mtpbrowser.h"
#include "tagssettings.h"
#include "pluginssettings.h"
#include "SessionsSettings.h"

QMtp::QMtp(QWidget *parent, const char *name, const QString& rcpath)
        : QMtp_base(parent, name), m_document() {

    // kick out this useless status bar
    delete statusBar();

    m_rcpath = rcpath;
    m_settings = 0;

    QAction *fileNewAction = new QAction( this, "fileNewAction" );
    connect( fileNewAction, SIGNAL( activated() ), this, SLOT( fileNew() ) );
    fileNewAction->setAccel( tr( "Ctrl+N" ) );

    connect(tabs,SIGNAL(currentChanged(QWidget*)),
            this, SLOT(slotCurrentPageChanged(QWidget*)));

    if (!loadConfigFile()) {
        QString default_content("<qnet/>");
        m_document.setContent(default_content);
    }

    loadStyleSheet();

    tabs->setTabPosition((QTabWidget::TabPosition)DomUtil::readIntEntry(m_document,"/appearance/tabs/position",QTabWidget::Top));
    fortune_page = 0;
    fproc = 0;
    if (DomUtil::readBoolEntry(m_document,"/remote/enabled",false))
        rctl = new RemoteControlServerInfo(this,DomUtil::readIntEntry(m_document,"/remote/port",5000),system_view,DomUtil::readEntry(m_document,"/remote/password",QString::null));
    else
        rctl=0;

    // plugins
    loadPlugins();

    // autoconnect
    QStringList list = DomUtil::readListEntry(m_document,"/general/sessions","session");
    for (QStringList::Iterator it = list.begin(); it != list.end(); ++it)
        if(DomUtil::readBoolEntry(m_document,"/sessions/" + *it + "/autoconnect",false))
            launchSession(*it);

    new_menu = new QPopupMenu(this);
    refreshMenu();
    fileMenu->insertItem(tr("New..."),new_menu,-1,0);
    connect(new_menu,SIGNAL(activated(int)),this,SLOT(launchSession(int)));
}


QMtp::~QMtp() {
    saveConfigFile();

    unloadPlugins();
}

QString QMtp::iconPath() {
    return DomUtil::readEntry(m_document,"/general/icon",QString::null);
}

void QMtp::slotConfigure() {
    m_settings = new MtpSettings(this);

    temporary_dom.setContent(m_document.toString());

    // Select the right widget
    connect(m_settings->prop_list, SIGNAL(highlighted(int)),
            m_settings->stack, SLOT(raiseWidget(int)));

    // Sessions :

    SessionsSettings * sessions_settings = new SessionsSettings(m_settings->stack);
    m_settings->stack->addWidget(sessions_settings,0);
    m_settings->prop_list->insertItem("Sessions",0);
    {
        QStringList list = DomUtil::readListEntry(m_document,"/general/sessions","session");
        for (QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
            QString name = *it;
            QString host = DomUtil::readEntry(m_document,"/sessions/" + name + "/host","");
            QString port = DomUtil::readEntry(m_document,"/sessions/" + name + "/port","");
            QString login = DomUtil::readEntry(m_document,"/sessions/" + name + "/login","");
            QString password = DomUtil::readEntry(m_document,"/sessions/" + name + "/password","");
            bool autoconnect = DomUtil::readBoolEntry(m_document,"/sessions/" + name + "/autoconnect",false);
            SessionsSettings::SessionItem session(name,host,port,login,password,autoconnect);
            sessions_settings->addSessionItem(session);
        }
    }

    // Stylesheet :
    TagsSettings * tags_settings = new TagsSettings(m_settings->stack);
    m_settings->stack->addWidget(tags_settings,1);
    m_settings->prop_list->insertItem("StyleSheet",1);
    {
        QStringList tags = DomUtil::readListEntry(m_document,"/general/tags","tag");
        for(QStringList::ConstIterator it = tags.begin(); it != tags.end(); ++it) {
            QString name = *it;
            QString family = DomUtil::readEntry(m_document,"/appearance/tags/" + *it + "/family");
            QString style = DomUtil::readEntry(m_document,"/appearance/tags/" + *it + "/style");
            int color = DomUtil::readIntEntry(m_document,"/appearance/tags/" + *it + "/color");
            bool strike = DomUtil::readBoolEntry(m_document,"/appearance/tags/" + *it + "/strike");
            bool underline = DomUtil::readBoolEntry(m_document,"/appearance/tags/" + *it + "/underline");
            bool spaces = DomUtil::readBoolEntry(m_document,"/appearance/tags/" + *it + "/spaces");
            int size = DomUtil::readIntEntry(m_document,"/appearance/tags/" + *it + "/size");
            TagItem tag(name,family,style,color,strike,underline,spaces,size);
            tags_settings->addTagItem(tag);
        }
    }

    // Plugins :
    PluginsSettings * plugins_settings = new PluginsSettings(m_settings->stack);
    m_settings->stack->addWidget(plugins_settings,2);
    m_settings->prop_list->insertItem("Plugins",2);
    {
        QStringList tags = DomUtil::readListEntry(m_document,"/general/plugins","file");
        plugins_settings->plugins_box->insertStringList(tags);
    }

    // Filters :
    {
        MtpFiltersSettings * filters_settings = new MtpFiltersSettings(m_settings->stack);
        m_settings->stack->addWidget(filters_settings,3);
        m_settings->prop_list->insertItem("Filters",3);
        filters_settings->setDom(&temporary_dom);
    }

    // Urls :
    UrlSettings * url_settings = new UrlSettings(m_settings->stack);
    m_settings->stack->addWidget(url_settings,4);
    m_settings->prop_list->insertItem("Url",4);
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
    PrefixSettings * prefix_settings = new PrefixSettings(m_settings->stack);
    m_settings->stack->addWidget(prefix_settings,5);
    m_settings->prop_list->insertItem("Prefixes",5);
    {
        QStringList list = DomUtil::readListEntry(m_document,"/prefixes","item");
        for (QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
            PrefixSettings::PrefixItem mng(*it);
            prefix_settings->addPrefixItem(mng);
        }
    }

    // Fortune :
    FortuneSettings * fortune_settings = new FortuneSettings(m_settings->stack);
    m_settings->stack->addWidget(fortune_settings,6);
    m_settings->prop_list->insertItem("Fortune",6);
    {
        QString args = DomUtil::readEntry(m_document,"/fortune");
        fortune_settings->fortune_edit->setText(args);
    }

    // Appearance :
    AppearanceSettings * appearance_settings = new AppearanceSettings(m_settings->stack);
    m_settings->stack->addWidget(appearance_settings,7);
    m_settings->prop_list->insertItem("Appearance",7);
    {
        int position = DomUtil::readIntEntry(m_document,"/appearance/tabs/position",QTabWidget::Top);
        appearance_settings->rbTop->setChecked(position==QTabWidget::Top);
        appearance_settings->rbBottom->setChecked(!appearance_settings->rbTop->isChecked());
    }

    connect(m_settings, SIGNAL(end()),
            SLOT(slotStoreConfig()));

    m_settings->show();
}

void QMtp::slotStoreConfig() {
    if (m_settings->result() == QDialog::Accepted) {

        SessionsSettings * sessions_settings = (SessionsSettings *)m_settings->stack->widget(0);
        TagsSettings * tags_settings = (TagsSettings *)m_settings->stack->widget(1);
        PluginsSettings * plugins_settings = (PluginsSettings *)m_settings->stack->widget(2);
        MtpFiltersSettings * filters_settings = (MtpFiltersSettings *)m_settings->stack->widget(3);
        UrlSettings * url_settings = (UrlSettings *)m_settings->stack->widget(4);
        PrefixSettings * prefix_settings = (PrefixSettings *)m_settings->stack->widget(5);
        FortuneSettings * fortune_settings = (FortuneSettings *)m_settings->stack->widget(6);
        AppearanceSettings * appearance_settings = (AppearanceSettings *)m_settings->stack->widget(7);

        filters_settings->apply();

        m_document.setContent(temporary_dom.toString());

        for(QValueList<ChatSession*>::Iterator it = sessions.begin(); it != sessions.end(); ++it) {
            (*it)->updateFilters();
        }

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

        // StyleSheet :
        {
            QStringList l;
            for (uint i=0; i< tags_settings->tags_box->count(); i++)
                l << tags_settings->tags_box->text(i);
            DomUtil::writeListEntry(m_document,"/general/tags","tag",l);

            for(uint i=0; i<tags_settings->tags_box->count(); i++) {
                TagItem it = *(tags_settings->map.find(tags_settings->tags_box->text(i)));
                DomUtil::writeEntry(m_document,"/appearance/tags/" + it.name + "/family",it.family);
                DomUtil::writeEntry(m_document,"/appearance/tags/" + it.name + "/style",it.style);
                DomUtil::writeIntEntry(m_document,"/appearance/tags/" + it.name + "/color",it.color);
                DomUtil::writeBoolEntry(m_document,"/appearance/tags/" + it.name + "/strike",it.strike);
                DomUtil::writeBoolEntry(m_document,"/appearance/tags/" + it.name + "/underline",it.underline);
                DomUtil::writeBoolEntry(m_document,"/appearance/tags/" + it.name + "/spaces",it.collapse);
                DomUtil::writeIntEntry(m_document,"/appearance/tags/" + it.name + "/size",it.size);
            }
//            loadStyleSheet();
        }

        // Sessions :
        {
            QStringList l;
            for (uint i=0; i< sessions_settings->sessions_box->count(); i++)
                l << sessions_settings->sessions_box->text(i);
            DomUtil::writeListEntry(m_document,"/general/sessions","session",l);

            QDomElement child = DomUtil::elementByPath(m_document,"/sessions");
            if(!child.isNull()) child.parentNode().removeChild(child);

            for (uint i=0; i< sessions_settings->sessions_box->count(); i++) {
                SessionsSettings::SessionItem it = *(sessions_settings->map.find(sessions_settings->sessions_box->text(i)));
                DomUtil::writeEntry(m_document,"/sessions/" + it.name + "/host",it.host);
                DomUtil::writeEntry(m_document,"/sessions/" + it.name + "/port",it.port);
                DomUtil::writeEntry(m_document,"/sessions/" + it.name + "/login",it.login);
                DomUtil::writeEntry(m_document,"/sessions/" + it.name + "/password",it.password);
                DomUtil::writeBoolEntry(m_document,"/sessions/" + it.name + "/autoconnect",it.autoconnect);
            }
            refreshMenu();
        }

        // Plugins :
        {
            QStringList tags;
            for (uint i=0; i< plugins_settings->plugins_box->count(); i++)
                tags << plugins_settings->plugins_box->text(i);
            bool reload = (tags != DomUtil::readListEntry(m_document,"/general/plugins","file"));
            DomUtil::writeListEntry(m_document,"/general/plugins","file",tags);
            if (reload) {
                unloadPlugins();
                loadPlugins();
            }
        }


        saveConfigFile();
    }
    delete m_settings;
    m_settings = 0;
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

Page * QMtp::getNewPage(const QString& type,const QString& name,ChatSession * ref, bool pop) {
    QMap<QString,void*>::Iterator it;
    if((it = plugins_map.find(type)) != plugins_map.end()) {
        create_t* create_plugin = (create_t*) dlsym(*it, "create");
        Page* page = create_plugin(tabs,name,ref);
        int index=tabs->indexOf(ref->chatpage());
        if (page->isSlave()) {
            tabs->insertTab(page,name,index+1);
            if(pop)
                tabs->showPage(page);
            tabs->currentPage()->setFocus();
        }
        tab_map.insert(page,ref);
        connect(page, SIGNAL(textDisplayed(QWidget *)),
                this, SLOT(slotTextDisplayed(QWidget *)));
        return page;
    }
    system_view->append("ERROR: No plugin \"" + type + "\" available. Perhaps you should load lib" + type + ".so\n");
    return 0;
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
            tab_map.remove(it);
        } else // session tab
            sessions.remove((ChatSession*)((Page*)w)->getMaster());
        delete w;
    }
}

void QMtp::fileExit() {
    saveConfigFile();
    close();
    emit closeProgram();
}

void QMtp::fileSaveAs() {
    QWidget* w = tabs->currentPage();
    if(w != tab && w != fortune_page) {

        QString log = QString::null;

        QMap<QWidget*,ChatSession*>::Iterator it;
        if ((it = tab_map.find(w)) != tab_map.end()) {
            log = (static_cast<Page*>(w))->getText();
        }
        else {// session tab
            log = (static_cast<MainChatPage*>(w))->chat_view->getText();
        }

        if(log != QString::null) {
            QString filename(QFileDialog::getSaveFileName());
            if(!filename.isNull()) {
                QFile file(filename);
                if(file.open(IO_WriteOnly)) {
                    QTextStream stream( &file );
                    stream << log;
                    file.close();
                } else {
                    QMessageBox::critical(this,"Error","Unable to write file");
                }
            }
        } else
            QMessageBox::critical(this,"Error","Log fonction not implemented yet !");
    }
}

bool QMtp::loadConfigFile() {
    QFile fin(rcPath());
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
    QFile fout(rcPath());
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

        tabs->insertTab(fortune_page,"Fortune");
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

void QMtp::refreshMenu() {
    new_menu->clear();
    QStringList list = DomUtil::readListEntry(m_document,"/general/sessions","session");
    int i = 0;
    for (QStringList::Iterator it = list.begin(); it != list.end(); ++it,++i)
        new_menu->insertItem(*it,i);

}

void QMtp::loadStyleSheet() {
    QFontDatabase db;
    QStyleSheet * qnet_style = new QStyleSheet(this);
    QStringList tags = DomUtil::readListEntry(m_document,"/general/tags","tag");
    for(QStringList::ConstIterator it = tags.begin(); it != tags.end(); ++it) {
        QStyleSheetItem *item = new QStyleSheetItem(qnet_style,*it);
        QString family = DomUtil::readEntry(m_document,"/appearance/tags/" + *it + "/family");
        QString style = DomUtil::readEntry(m_document,"/appearance/tags/" + *it + "/style");
        int color = DomUtil::readIntEntry(m_document,"/appearance/tags/" + *it + "/color");
        bool strike = DomUtil::readBoolEntry(m_document,"/appearance/tags/" + *it + "/strike");
        bool underline = DomUtil::readBoolEntry(m_document,"/appearance/tags/" + *it + "/underline");
        bool spaces = DomUtil::readBoolEntry(m_document,"/appearance/tags/" + *it + "/spaces");
        int size = DomUtil::readIntEntry(m_document,"/appearance/tags/" + *it + "/size");

        item->setFontFamily(family);
        item->setFontItalic(db.italic(family, style));
        if(db.bold(family, style))
            item->setFontWeight(QFont::Bold);
        item->setColor(color);
        item->setFontStrikeOut(strike);
        item->setFontUnderline(underline);
        if(!spaces)
            item->setWhiteSpaceMode(QStyleSheetItem::WhiteSpacePre);
        item->setLogicalFontSize(size);
    }
    QStyleSheet::setDefaultSheet(qnet_style);
}

void QMtp::launchSession(const QString& name) {
    ChatSession * session = new ChatSession(name,this,tabs,0,&m_document);
    session->chatpage()->toggleUserMenu(false);
    sessions.push_back(session);

    tabs->insertTab(session->chatpage(),"@" + name);
    tabs->showPage(session->chatpage());

    connect(session->chatpage(), SIGNAL(textDisplayed(QWidget *)),
            this, SLOT(slotTextDisplayed(QWidget *)));
}

void QMtp::launchSession(int index) {
    QStringList list = DomUtil::readListEntry(m_document,"/general/sessions","session");
    this->launchSession(list[index]);
}

void QMtp::loadPlugins() {
    QStringList plugs = DomUtil::readListEntry(m_document,"/general/plugins","file");
    for(QStringList::Iterator it = plugs.begin(); it != plugs.end(); ++it)
        loadPlugin(*it);
}

void QMtp::unloadPlugins() {
    // unload plugins :
    for (QMap<QString,void*>::Iterator it = plugins_map.begin(); it != plugins_map.end(); ++it) {
        system_view->append("Unloading " + it.key());
        dlclose(*it);
    }
    plugins_map.clear();
}
