/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "ChatSession.h"
#include "telnetmanager.h"
#include <qstring.h>
#include <qstringlist.h>
#include <qregexp.h>
#include <qstylesheet.h>
#include <qaction.h>
#include <qkeysequence.h>
#include <qprocess.h>
#include "mtpbrowser.h"
#include <qlineedit.h>
#include <qlistbox.h>
#include <iostream>
#include "mtpfilterssettings.h"
#include "qnet.h"
#include "domutil.h"
#include "MtpFilter.h"
#include "MtpContext.h"
#include <qmessagebox.h>
#include <qtextedit.h>
#include <qapplication.h>
#include "page.h"
#include <qglobal.h>

ChatSession::ChatSession(const QString& session_name, QMtp * mtp, QWidget *parent, const char *name, QDomDocument * dom)
        : ChatPage(parent, name) {
    
    host = DomUtil::readEntry(*dom,"/sessions/" + session_name + "/host","");
    port = DomUtil::readEntry(*dom,"/sessions/" + session_name + "/port","");
    this->mtp = mtp;
    this->m_dom = dom;
    this->session_name = session_name;

/*    mng = new TelnetManager(this);
    mng->setArgs(host,port);
    mng->setLogin(DomUtil::readEntry(*dom,"/sessions/" + session_name + "/login",""));
    mng->setPassword(DomUtil::readEntry(*dom,"/sessions/" + session_name + "/password",""));
    mng->start();*/
    
    createTelnetManager();

    displayStderr("Connecting to " + host + ":" + port);

    chat_view->setTextFormat(Qt::RichText);

    chat_view->setWrapPolicy(QTextBrowser::Anywhere);
    chat_view->setLinkUnderline(true);

    item = new QStyleSheetItem(chat_view->styleSheet(),"mypre");
    item->setWhiteSpaceMode(QStyleSheetItem::WhiteSpacePre);


    login_set = false;
    enable_stdout = true;
    receiving_who = false;
    position = 0;

    history_up = new QAction(chat_edit,"up");
    history_up->setAccel(QKeySequence(SHIFT + Key_Up));
    history_down = new QAction(chat_edit,"down");
    history_down->setAccel(QKeySequence(SHIFT + Key_Down));
    new_line = new QAction(chat_edit,"new");
    new_line->setAccel(QKeySequence(CTRL + Key_Return));
    complete = new QAction(chat_edit,"complete");
    complete->setAccel(QKeySequence(Key_Tab));
    reconnect = new QAction(this,"reconnect");
    reconnect->setAccel(QKeySequence(CTRL + Key_R));
    pgup = new QAction(chat_edit,"pgup");
    pgup->setAccel(QKeySequence(Key_PageUp));
    pgdown = new QAction(chat_edit,"pgdown");
    pgdown->setAccel(QKeySequence(Key_PageDown));

    connect(history_up, SIGNAL(activated()),
            this, SLOT(slotHistoryUp()));
    connect(history_down, SIGNAL(activated()),
            this, SLOT(slotHistoryDown()));
    connect(new_line, SIGNAL(activated()),
            this, SLOT(slotNewLine()));
    connect(complete, SIGNAL(activated()),
            this, SLOT(slotComplete()));
    connect(reconnect, SIGNAL(activated()),
            this, SLOT(slotReconnect()));

    connect(mng, SIGNAL(processExited()),
            this, SLOT(closeSession()));

    connect(chat_view,SIGNAL(linkClicked(const QString &)),
            this, SLOT(slotLinkClicked(const QString &)));

    connect(chat_edit, SIGNAL(returnPressed()),
            this, SLOT(returnPressed()));

    connect(pgup,SIGNAL(activated()),
            this,SLOT(slotPageUp()));
    connect(pgdown,SIGNAL(activated()),
            this,SLOT(slotPageDown()));

//     connect(users_box, SIGNAL(doubleClicked(QListBoxItem*)),
//             this,SLOT(slotUserDoubleClicked(QListBoxItem*)));
    
    chat_edit->setFocus();
    chat_edit->setWordWrap(QTextEdit::NoWrap);
    chat_edit->setTextFormat(Qt::PlainText);

    doc_source = chat_view->source();
    history_iterator = 0;

    //proc = new QProcess(this);
    m_filter = new MtpFilter(dom,context());
//    context() = new MtpContext();

    setFocusProxy(chat_edit);
}


ChatSession::~ChatSession() {
    //delete mng;
    delete m_filter;
    for (std::vector<Page*>::iterator it = brothers.begin(); it != brothers.end(); ++it)
        delete (*it);
}

void ChatSession::displayStderr(const QString& msg) {
    mtp->system_view->append("["+ host + ":" + port + "]" + msg);
}

void ChatSession::displayStdout(const QString& msg) {

    emit outputMessage(msg);
    QString m(msg);
    QString output;
    
    if (m.startsWith("<Mtp> Welcome")) {
        this->login = m.replace(QRegExp("<Mtp> Welcome, "),"").replace(QRegExp("\\..*"),"");
        displayStderr("Setting user name to " + this->login + ".");

        context()->setVar("login",caseUnsensitive(this->login));
        context()->setVar("Login",this->login);
        context()->setVar("channel","Hall");

        QString new_m("<Mtp> Welcome, " + login + ".");

        escape(&new_m);
        new_m = m_filter->filterOut(new_m);
#if (QT_VERSION < 305)
        new_m += "<br>";
#endif

        output = Filter::expandVars(new_m,context());
        unescape(&output);
        chat_view->append(output);

        position += new_m.length();
        login_set = true;
        mng->writeStdin(QString("set client ") + CLIENT);
        getInfo();
    } else if(filter(&m)) {
        escape(&m);
        m = m_filter->filterOut(m);

        QStringList list = QStringList::split("\n",m);
        for(QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
            QString mm = *it;
#if (QT_VERSION < 305)
            mm += "<br>";
#endif

            QRegExp rx("^(-?):(\\w+\\?" "?):(\\w+):(.*)");
            if (rx.exactMatch(mm)) {
                QString m(rx.cap(4));
#if (QT_VERSION < 305)
                m += "<br>";
#endif

                bool ok(!(rx.cap(2).endsWith("?")));
                QString abbrev = ok ? rx.cap(2) : rx.cap(2).left(rx.cap(2).length()-1);

                for (std::vector<Page*>::iterator it = brothers.begin(); it != brothers.end(); ++it)
                    if ((*it)->name() == rx.cap(3)) {

                        output = Filter::expandVars(m,context());
                        unescape(&output);
                        (*it)->append(output);
                        ok = false;
                    }
                if (ok) {

                    Page * edit = mtp->getNewPage(abbrev,rx.cap(3),this,rx.cap(1)!="-");
                    if(edit) {
                        brothers.push_back(edit);
                        output = Filter::expandVars(m,context());
                        unescape(&output);
                        edit->append(output);
                    }
                    else
                        displayStderr("Don't know what to do with : " + mm);
                }
            } else {
                output = Filter::expandVars(mm,context());
                unescape(&output);
                chat_view->append(output);
                emit textDisplayed(this);
            }
        }
    }
}

const QString & ChatSession::sessionName() const {
    return session_name;
}

void ChatSession::kill(Page * ref) {
    for (std::vector<Page*>::iterator it = brothers.begin(); it != brothers.end(); ++it)
        if ((*it) == ref) {
            brothers.erase(it);
            return;
        }
}

void ChatSession::returnPressed() {


    // delete this $#!@? "\n" we've just inserted
    chat_edit->doKeyboardAction(QTextEdit::ActionBackspace);

    // put in history if and ONLY if password is already set...
    if (login_set && (chat_edit->text() != history[0]))
        history.push_front(chat_edit->text());

    QString m(chat_edit->text());
    send(m);
    chat_edit->clear();

    // history returns to start
    history_iterator = 0;

}

void ChatSession::send(const QString & m) {
    QString msg(m);

    QString prefix = "";
    // Compute the prefix
    QStringList l = DomUtil::readListEntry(*m_dom,"/prefixes","item");
    for (QStringList::Iterator it = l.begin(); it != l.end(); ++it) {
        QRegExp re("^(" + (*it).replace(QRegExp("%l"),"[^ ]*") + ") .*");
        if (re.exactMatch(msg)) {
            prefix = re.cap(1) + " ";
            break;
        }
    }

    // Delete prefix in string
    msg = msg.right(msg.length() - prefix.length());

    // split the input into atomic pieces
    QStringList list = QStringList::split("\n",msg);
    for (QStringList::Iterator it = list.begin(); it != list.end(); ++it) {

        // For looooong messages, break on last possible space
        QString m = *it;
        unsigned int limit = CHAT_BUFFER_LENGTH - prefix.length();
        while (m.length() > limit) {
            int last_space = m.findRev(' ',limit);
            if(last_space == -1) last_space = limit;
            
            mng->writeStdin(prefix + m.left(last_space));
            m = msg.right(m.length() - last_space);
        }
        QString to_send(prefix + m);
        mng->writeStdin(m_filter->filterIn(to_send));
    }


}

void ChatSession::ensureFocus() {
    chat_edit->setFocus();
}

void ChatSession::closeSession() {
    QMessageBox::information(this,"Connection lost","Lost connection with host " + host);
}

void ChatSession::slotLinkClicked(const QString & link) {

    QStringList list = DomUtil::readListEntry(*m_dom,"/urls/available","type");
    for(QStringList::Iterator it = list.begin(); it != list.end(); ++it)
        if(link.startsWith(*it))
            executeShellCommand(DomUtil::readEntry(*m_dom,QString("/urls/" + *it + "/command")).replace(QRegExp("%l"),link));
}

void ChatSession::slotHistoryUp() {

    if (history_iterator == 0)
        history_iterator=history.begin();
    else if (history_iterator != (--history.end()))
        history_iterator++;
    chat_edit->setText(*history_iterator);
}

void ChatSession::slotHistoryDown() {
    if( history_iterator == 0)
        return;
    if (history_iterator != history.begin()) {
        history_iterator--;
        chat_edit->setText(*history_iterator);
    } else {
        chat_edit->clear();
        history_iterator = 0;
    }
}

void ChatSession::slotNewLine() {
    chat_edit->doKeyboardAction(QTextEdit::ActionReturn);
}

void ChatSession::slotComplete() {
    int para, index;
    //    chat_edit->doKeyboardAction(QTextEdit::ActionBackspace);
    chat_edit->getCursorPosition(&para,&index);
    QString parag = chat_edit->text(para);
    QString pref;

    if (!parag.at(index-1).isLetterOrNumber())
        return;

    while (parag.at(--index).isLetterOrNumber()) {
        pref = parag.at(index) + pref;
        chat_edit->doKeyboardAction(QTextEdit::ActionBackspace);
    }
    for(uint i=0; i<users_box->count(); i++)
        //if (users_box->text(i).startsWith(pref)) {
        if (!(users_box->text(i).find(pref,0,false))) {
            if (users_box->text(i) == pref) {
                uint position = (i+1)%(users_box->count());
                chat_edit->insertAt(users_box->text(position),para,++index);
                chat_edit->setCursorPosition(para,index+users_box->text(position).length());
            } else {
                chat_edit->insertAt(users_box->text(i),para,++index);
                chat_edit->setCursorPosition(para,index+users_box->text(i).length());
            }
            return;
        }
    chat_edit->insertAt(pref,para,++index);
    chat_edit->setCursorPosition(para,index+pref.length());
}

void ChatSession::slotReconnect() {
    delete mng;
    emit inactive();
    createTelnetManager();
    emit active();
}

void ChatSession::slotPageUp() {
    chat_view->moveCursor(QTextEdit::MovePgUp,false);
}

void ChatSession::slotPageDown() {
    chat_view->moveCursor(QTextEdit::MovePgDown,false);
}

void ChatSession::slotUserDoubleClicked(QListBoxItem* item) {
    if(!item) return;
    displayStdout(":tell:" + item->text() +": ");
}

void ChatSession::escape(QString * msg) {
    *msg = msg->replace(QRegExp("&"),"&amp ")
        .replace(QRegExp("<"),"&lt ")
        .replace(QRegExp(">"),"&gt ")
        .replace(QRegExp("\\\\"),"&bks ");
}

void ChatSession::unescape(QString * msg) {
    *msg = msg->replace(QRegExp("&bks "),"\\");
}

bool ChatSession::filter(QString * msg) {
    if (msg->startsWith("\a")) {
        *msg = msg->replace(QRegExp("^\a"),"");
    }

    QRegExp beep("^[0-9: ]*<Mtp> ([^ ]*) beeps you.*");
    if (beep.exactMatch(*msg))
        QApplication::beep();

    QRegExp user_out("^[0-9: ]*<Mtp> ([^ ]*) (leaves|disconnects|is kicked out).*");
    if (user_out.exactMatch(*msg))
        removeUser(user_out.cap(1));

    QRegExp user_kick("^[0-9: ]*<Mtp> You kick ([^ ]*) out.*");
    if (user_kick.exactMatch(*msg))
        removeUser(user_kick.cap(1));

    QRegExp user_in("^[0-9: ]*<Mtp> ([^ ]*) (comes in ?!).*");
    if (user_in.exactMatch(*msg))
        addUser(user_in.cap(1));



    if (msg->startsWith(" Login")) {

        if (who_demanded) {
            receiving_who = true;
            displayStderr("Getting informations about connected users");
            who_demanded = false;
            enable_stdout = false;
        }
        return enable_stdout;
    }

    if (msg->startsWith("-----")) {
        if(receiving_who)
            users_box->clear();
        return (enable_stdout);
    }

    if (msg->startsWith("<Mtp> There ")) {
        bool tmp = this->enable_stdout;
        this->enable_stdout = true;
        this->receiving_who = false;
        users_box->sort();
        return tmp;
    }

    if (receiving_who) {
        QString login(*msg);
        this->users_box->insertItem(login.replace(QRegExp(" .*"),""));
        return enable_stdout;
    }

    //    if (msg->startsWith("<Mtp> Password:"))
    //        chat_edit->setEchoMode(QLineEdit::Password);

    return true;
}

void ChatSession::getInfo() {
    who_demanded = true;
    mng->writeStdin("who all");
}

QString ChatSession::caseUnsensitive(const QString& msg) {
    QString up = msg.upper();
    QString low = msg.lower();
    QString res("");
    for (unsigned int i = 0; i<msg.length(); i++)
        res += "[" + up.at(i) + low.at(i) + "]";
    return res;
}

void ChatSession::addUser(const QString& name) {
    users_box->insertItem(name);
    users_box->sort();
}

void ChatSession::removeUser(const QString& name) {
    QListBoxItem * item = users_box->findItem(name,Qt::ExactMatch);
    delete item;
}

void ChatSession::executeShellCommand(const QString& com) {
    //    if (!proc->isRunning()) {
    proc = new QProcess(this);
    QStringList list = QStringList::split(" ",com);
    proc->setArguments(list);
    proc->start();
    connect(proc, SIGNAL(processExited()),
            this, SLOT(deleteProcess()));
    //    }
}

void ChatSession::setDomDocument(QDomDocument * dom) {
    m_dom = dom;
}

void ChatSession::deleteProcess() {
    delete sender();
}

void ChatSession::createTelnetManager()
{
    mng = new TelnetManager(this);
    mng->setArgs(host,port);
    mng->setLogin(DomUtil::readEntry(*m_dom,"/sessions/" + session_name + "/login",""));
    mng->setPassword(DomUtil::readEntry(*m_dom,"/sessions/" + session_name + "/password",""));
    mng->start();
}

QMtp* ChatSession::topLevel() const {
    return mtp;
}

void ChatSession::updateFilters() {
    MtpFilter* f = m_filter;
    MtpFilter* g = new MtpFilter(m_dom,context());
    m_filter = g;
    f->setObsolete();
    delete f;
}
