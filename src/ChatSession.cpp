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

ChatSession::ChatSession(QString session_name, QMtp * mtp, QWidget *parent, const char *name, QDomDocument * dom)
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

    chat_edit->setFocus();
    chat_edit->setWordWrap(QTextEdit::NoWrap);
    chat_edit->setTextFormat(Qt::PlainText);

    doc_source = chat_view->source();
    history_iterator = 0;

    //proc = new QProcess(this);
    m_filter = new MtpFilter();
//    context() = new MtpContext();

    applyFilters();

}


ChatSession::~ChatSession() {
    //delete mng;
    for (std::vector<Page*>::iterator it = brothers.begin(); it != brothers.end(); ++it)
        delete (*it);
}

void ChatSession::displayStderr(QString msg) {
    mtp->system_view->append("["+ host + ":" + port + "]" + msg);
}

void ChatSession::displayStdout(QString msg) {

    emit outputMessage(msg);
    
    if (msg.startsWith("<Mtp> Welcome")) {
        this->login = msg.replace(QRegExp("<Mtp> Welcome, "),"").replace(QRegExp("\\..*"),"");
        displayStderr("Setting user name to " + this->login + ".");

        context()->setVar("login",caseUnsensitive(this->login));
        context()->setVar("Login",this->login);

        QString new_msg("<Mtp> Welcome, " + login + ".");

        escape(&new_msg);
        new_msg = m_filter->filterOut(new_msg);
#if (QT_VERSION < 305)
        new_msg += "<br>";
#endif

        chat_view->append(new_msg);

        position += new_msg.length();
        login_set = true;
        mng->writeStdin(QString("set client ") + CLIENT);
        getInfo();
    } else if(filter(&msg)) {
        escape(&msg);
        msg = m_filter->filterOut(msg);


        QStringList list = QStringList::split("\n",msg);
        for(QStringList::Iterator it = list.begin(); it != list.end(); ++it) {
            QString mmsg = *it;
#if (QT_VERSION < 305)
            mmsg += "<br>";
#endif

            QRegExp rx("^:(\\w+\\?" "?):(\\w+):(.*)");
            if (rx.exactMatch(mmsg)) {
                QString m(rx.cap(3));
#if (QT_VERSION < 305)
                m += "<br>";
#endif

                bool ok(!(rx.cap(1).endsWith("?")));
                QString abbrev = ok ? rx.cap(1) : rx.cap(1).left(rx.cap(1).length()-1);

                for (std::vector<Page*>::iterator it = brothers.begin(); it != brothers.end(); ++it)
                    if ((*it)->name() == rx.cap(2)) {

                        (*it)->append(m);

                        ok = false;
                    }
                if (ok) {

		    Page * edit = mtp->getNewPage(abbrev,rx.cap(2),this);
		    if(edit) {
			brothers.push_back(edit);
			edit->append(m);
		    }
		    else
			displayStderr("Don't know what to do with : " + mmsg);
                }
            } else {
                chat_view->append(mmsg);

                emit textDisplayed(this);
            }
        }
    }
}

const QString & ChatSession::sessionName() {
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

void ChatSession::send(QString & m) {
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

        // For looooong messages
        QString m = *it;
        unsigned int limit = CHAT_BUFFER_LENGTH - prefix.length();
        while (m.length() > limit) {
            mng->writeStdin(prefix + m.left(limit));
            m = msg.right(m.length() - limit);
        }
        QString to_send(prefix + m);
        mng->writeStdin(m_filter->filterIn(to_send));
    }


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
    createTelnetManager();
}

void ChatSession::escape(QString * msg) {

    *msg = msg->replace(QRegExp("<"),"&lt ").replace(QRegExp(">"),"&gt ");


}

bool ChatSession::filter(QString * msg) {
    if (msg->startsWith("\a")) {
        *msg = msg->replace(QRegExp("^\a"),"");
    }

    QRegExp beep("^[0-9: ]*<Mtp> ([^ ]*) beeps you");
    if (beep.exactMatch(*msg))
        QApplication::beep();

    QRegExp user_out("^[0-9: ]*<Mtp> ([^ ]*) (leaves|disconnects|is kicked out).*");
    if (user_out.exactMatch(*msg))
        removeUser(user_out.cap(1));

    QRegExp user_kick("^[0-9: ]*<Mtp> You kick ([^ ]*) out.*");
    if (user_kick.exactMatch(*msg))
        removeUser(user_kick.cap(1));

    QRegExp user_in("^[0-9: ]*<Mtp> ([^ ]*) (comes in !).*");
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

QString ChatSession::caseUnsensitive(QString msg) {
    QString up = msg.upper();
    QString low = msg.lower();
    QString res("");
    for (unsigned int i = 0; i<msg.length(); i++)
        res += "[" + up.at(i) + low.at(i) + "]";
    return res;
}

void ChatSession::addUser(QString name) {
    users_box->insertItem(name);
    users_box->sort();
}

void ChatSession::removeUser(QString name) {
    QListBoxItem * item = users_box->findItem(name,Qt::ExactMatch);
    delete item;
}

void ChatSession::executeShellCommand(QString com) {
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

void ChatSession::applyFilters() {
    applyLine("test_file",
	      "^(<.*>)?(\\d{2}:\\d{2}:\\d{2} )?(\\|\\w+\\| \\[Rainbow\\][^<]*)(<.*>)?",
	      "\\0\\\n:file:File:\\3\\");
    
    applyLine("ignore_warning",
	      "^(<.*>)?(\\d{2}:\\d{2}:\\d{2} )?&lt Mtp&gt  \\w+ is away and may not be hearing you(<.*>)?",
	      "");
    applyLine("join_dessin",
	      "^(<.*>)?(\\d{2}:\\d{2}:\\d{2} )?&lt Mtp&gt  You join channel Dessin(<.*>)?",
	      "\\0\\\n:drawing:Dessin:\n:affect::channel=Dessin");
    applyLine("draw_other",
	      "^(<.*>)?(\\d{2}:\\d{2}:\\d{2} )?(&lt \\w+&gt  )(\\}[LCT][^<]*)(<.*>)?",
	      ":drawing:Dessin:\\4\\");
    applyLine("tell_receive",
              "^(<.*>)?(\\d{2}:\\d{2}:\\d{2} )?(&lt Mtp&gt  )(\\w+) (tells you:|asks you:|replies:)([^<]*)(<.*>)?",
              ":tell:\\4\\: \\1\\&lt \\4\\&gt \\6\\\\7\\"
	      "\n:splash:spl:<\\4\\> \\6\\");
    applyLine("tell_emit",
              "^(<.*>)?(\\d{2}:\\d{2}:\\d{2} )?&lt Mtp&gt  You (tell|ask|reply to) (\\w+)(:)(.*)(<.*>)?",
              ":tell:\\4\\: \\1\\<font color=" + DomUtil::readEntry(*m_dom,"/colors/mytalk","black") + ">&lt \\Login\\&gt \\6\\</font>\\7\\");
    applyLine("notify_moves",
              "^(<.*>)?(\\d{2}:\\d{2}:\\d{2} )?(&lt Mtp&gt  )(\\w+) (is away|is back|leaves|disconnects|is kicked out|comes in)(.*)(<.*>)?",
              "\\1\\<font color=" + DomUtil::readEntry(*m_dom,"/colors/server","black") + ">\\2\\\\3\\\\4\\ \\5\\\\6\\\\7\\</font>\n"
              ":tell\?:\\4\\: \\1\\<font color=" + DomUtil::readEntry(*m_dom,"/colors/server","black") + ">\\3\\\\4\\ \\5\\\\6\\</font>\\7\\");

    applyLine("mytalk","^(<.*>)?(\\d{2}:\\d{2}:\\d{2} )?(&lt \\login\\&gt .*)(<.*>)?","\\1\\<font color=" + DomUtil::readEntry(*m_dom,"/colors/mytalk","black") + ">\\2\\\\3\\</font>\\4\\");
    applyLine("emote","^(<.*>)?(\\d{2}:\\d{2}:\\d{2} )?(&lt Mtp&gt  \\*.*)(<.*>)?","\\1\\<font color=" + DomUtil::readEntry(*m_dom,"/colors/emote","black") + ">\\2\\\\3\\</font>\\4\\");
    applyLine("me","^(<.*>)?(\\d{2}:\\d{2}:\\d{2} )?(&lt Mtp&gt .*you:.*)(<.*>)?","\\1\\<font color=" + DomUtil::readEntry(*m_dom,"/colors/me","black") + ">\\2\\\\3\\</font>\\4\\");
    applyLine("other","^(<.*>)?(\\d{2}:\\d{2}:\\d{2} )?(&lt Mtp&gt  You.*)(<.*>)?","\\1\\<font color=" + DomUtil::readEntry(*m_dom,"/colors/other","black") + ">\\2\\\\3\\</font>\\4\\");
    applyLine("server","^(<.*>)?(\\d{2}:\\d{2}:\\d{2} )?(&lt Mtp&gt .*)(<.*>)?","\\1\\<font color=" + DomUtil::readEntry(*m_dom,"/colors/server","black") + ">\\2\\\\3\\</font>\\4\\");
    applyLine("aboutme","(:\\w+:\\w+:)?(<.*>)?(\\d{2}:\\d{2}:\\d{2} )?(&lt .*\\login\\[^<]*)(<.*>)?",
	      "\\1\\<font color=" + DomUtil::readEntry(*m_dom,"/colors/aboutme","black") + ">\\2\\\\3\\\\4\\\\5\\</font>"
	      "\n:splash:spl:\\2\\\\3\\\\4\\");
    applyLine("aboutme2","(:\\w+:\\w+:)?(.*\\login\\.*)",
	      "\\1\\<font color=" + DomUtil::readEntry(*m_dom,"/colors/aboutme","black") + ">\\2\\</font>");
    applyLine("default","(:\\w+:\\w+:)?(.*)","\\1\\<font color=" + DomUtil::readEntry(*m_dom,"/colors/default","black") + ">\\2\\</font>");

    QString fname("format");
    GlobalFilter * f1 = new GlobalFilter(fname);
    QString pattern("<mypre>\\0\\</mypre>");
    f1->setResultPattern(pattern);
    f1->enable();
    m_filter->addGlobalFilter(f1);

    /*    {QString iname("test");
        InputFilter * f = new InputFilter(iname,false,context());
        QString ipat("execute : \\1\\");
        f->setResultPattern(ipat);
        QString input("!(.*)");
        f->setRegExp(input);
        f->enable();
        m_filter->addInputFilter(f);}
      */

    {// Block filter try on "wall" command
        QString iname("wall_emit");
        InputFilter * f = new InputFilter(iname,true,context());
        QString ipat("\\0\\");
        f->setResultPattern(ipat);
        QString input("wall");
        f->setRegExp(input);
        f->enable();
        m_filter->addInputFilter(f);


        QString bname("wall");
        BlockFilter * f2 = new BlockFilter(bname,context());
        QString pat(":browser:Wall: \\1\\<font face=fixed size=3>\\2\\</font>\\3\\");
        f2->setResultPattern(pat);
        QString beg("^(<.*>)?(&lt Mtp&gt  Wall :)(<.*>)?");
        f2->setBeginRegExp(beg);
        QString end("^(<.*>)?&lt Mtp&gt  End of Wall(<.*>)?");
        f2->setEndRegExp(end);
        f2->setInputDependency(f);
        f2->enable();
        f2->setPolicy(Filter::Transient);
        m_filter->addBlockFilter(f2);
        // end of try
    }

    {// Block filter try on "finger" command
        QString iname("finger_emit");

        QString bname("finger");
        BlockFilter * f2 = new BlockFilter(bname,context());
        QString pat(":id:Finger: \\0\\");
        f2->setResultPattern(pat);
        QString beg("^(<.*>)?(Login *: \\w+)(<.*>)?");
        f2->setBeginRegExp(beg);
        QString end("^(<.*>)?&lt Mtp&gt  End of finger(<.*>)?");
        f2->setEndRegExp(end);

        f2->enable();
        f2->setPolicy(Filter::Transient);
        m_filter->addBlockFilter(f2);
        // end of try
    }
    
    {// Block filter try on info command
        QString bname("info");
        BlockFilter * f2 = new BlockFilter(bname,context());
        QString pat("\\1\\<font face=fixed size=2>\\2\\</font>\\3\\");
        f2->setResultPattern(pat);
        QString beg("^(<.*>)?([^&<][^<]*|&lt Mtp&gt  History[^<]*|&lt Mtp&gt  System[^<]*|&lt Mtp&gt  Help[^<]*)(<.*>)?");
        f2->setBeginRegExp(beg);
        QString end("^(<.*>)?&lt [^<]*(<.*>)?");
        f2->setEndRegExp(end);
        f2->enable();
        f2->setPolicy(Filter::Transient);
        m_filter->addBlockFilter(f2);
        // end of try
    }

    // Url management
    QStringList list = DomUtil::readListEntry(*m_dom,"/urls/available","type");
    if (list.size()) {
        QString urls = DomUtil::readEntry(*m_dom,"/urls/" + list[0] + "/motif");
        for(QStringList::Iterator it = ++list.begin(); it != list.end(); ++it)
            urls += "|" + DomUtil::readEntry(*m_dom,"/urls/" + *it + "/motif");


        applyItem("urls",
                  "(" + urls + ")([^\" <]*)([\" \n<])",
                  "<font color=\"" + DomUtil::readEntry(*m_dom,"/colors/url","black") + "\"><a href=\"\\1\\\\2\\\">\\1\\\\2\\</a></font>\\3\\");

    }


}

void ChatSession::applyLine(QString fname, QString reg, QString pat) {
    LineFilter * f1 = new LineFilter(fname,context());
    f1->setRegExp(reg);
    f1->setResultPattern(pat);
    f1->enable();
    m_filter->addLineFilter(f1);
}

void ChatSession::applyItem(QString fname, QString reg, QString pat) {
    ItemFilter * f1 = new ItemFilter(fname,context());
    f1->setRegExp(reg);
    f1->setResultPattern(pat);
    f1->enable();
    m_filter->addItemFilter(f1);
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

QMtp* ChatSession::topLevel() {
    return mtp;
}
