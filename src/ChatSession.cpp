/***************************************************************************
 *   Copyright (C) 2002 by Yann Hodique                                    *
 *   Yann.Hodique@lifl.fr                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include <qglobal.h>
#include <qaction.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qregexp.h>
#include <qkeysequence.h>
#include <qprocess.h>
#include <qlineedit.h>
#include <qlistbox.h>
#include <qmessagebox.h>
#include <qtextedit.h>
#include <qapplication.h>

#include <iostream>

#include "ChatSession.h"
#include "telnetmanager.h"
#include "mtpbrowser.h"
#include "mtpfilterssettings.h"
#include "qnet.h"
#include "domutil.h"
#include "MtpFilter.h"
#include "MtpContext.h"
#include "page.h"

ChatSession::ChatSession(const QString& session_name, QMtp * mtp, QWidget *parent, const char *name, QDomDocument * dom)
        : Master(parent, name) {

    host = DomUtil::readEntry(*dom,"/sessions/" + session_name + "/host","");
    port = DomUtil::readEntry(*dom,"/sessions/" + session_name + "/port","");
    this->mtp = mtp;
    this->m_dom = dom;
    this->session_name = session_name;

    createTelnetManager();

    displayStderr("Connecting to " + host + ":" + port);

    login_set = false;
    enable_stdout = true;
    receiving_who = false;
    position = 0;

    connect(mng, SIGNAL(processExited()),
            this, SLOT(closeSession()));

    m_filter = new MtpFilter(dom,context());
    m_chatpage = new MainChatPage(parent,name,this);

    connect(m_chatpage, SIGNAL(destroyed()),
            this, SLOT(deleteLater()));
}


ChatSession::~ChatSession() {
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
        m_chatpage->append(output);

        position += new_m.length();
        login_set = true;
        m_chatpage->chat_edit->setUndoRedoEnabled(true);
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

            QRegExp rx("^(-?):(\\w+\\?" "?):([^ :]+):(.*)");
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
//                     else {
//                         displayStderr("Don't know what to do with : " + QStyleSheet::escape(mm));
//                     }
                }
            } else {
                output = Filter::expandVars(mm,context());
                unescape(&output);
                m_chatpage->append(output);
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
        mng->writeStdin(Filter::expandVars(m_filter->filterIn(to_send),context()));
    }


}

void ChatSession::closeSession() {
    QMessageBox::information(m_chatpage,"Connection lost","Lost connection with host " + host);
}

void ChatSession::slotLinkClicked(const QString & link) {

    QStringList list = DomUtil::readListEntry(*m_dom,"/urls/available","type");
    for(QStringList::Iterator it = list.begin(); it != list.end(); ++it)
        if(link.startsWith(*it))
            executeShellCommand(DomUtil::readEntry(*m_dom,QString("/urls/" + *it + "/command")).replace(QRegExp("%l"),link));
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
        m_chatpage->removeUser(user_out.cap(1));

    QRegExp user_kick("^[0-9: ]*<Mtp> You kick ([^ ]*) out.*");
    if (user_kick.exactMatch(*msg))
        m_chatpage->removeUser(user_kick.cap(1));

    QRegExp user_in("^[0-9: ]*<Mtp> ([^ ]*) (comes in ?!).*");
    if (user_in.exactMatch(*msg))
        m_chatpage->addUser(user_in.cap(1));



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
            m_chatpage->users_box->clear();
        return (enable_stdout);
    }

    if (msg->startsWith("<Mtp> There ")) {
        bool tmp = this->enable_stdout;
        this->enable_stdout = true;
        this->receiving_who = false;
        m_chatpage->users_box->sort();
        return tmp;
    }

    if (receiving_who) {
        QString login(*msg);
        m_chatpage->users_box->insertItem(login.replace(QRegExp(" .*"),""));
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

void ChatSession::slotReconnect() {
    delete mng;
    emit inactive();
    createTelnetManager();
    emit active();
}

MainChatPage *ChatSession::chatpage() {
    return m_chatpage;
}
