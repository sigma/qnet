/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <qregexp.h>

enum {
        LOGIN,
        GROUP,
	NAME,
	EMAIL,
	FORMATION,
	REGISTERED,
	BIRTHDAY,
	KICKNB,
	KICKEDNB,
	VAR, //on since / last on
	HOST,
	CLIENT,
	CHANNEL,
	IDLE,
	LOGINNB,
	TOTAL,
	PLAN
    };

void IdForm::append(const QString& msg) {
    QString m(msg);
    switch( state++ ) {
    case LOGIN:
	login_label->setText("<h2>" + m.replace(QRegExp("Login      : "),"") + "</h2>");
	plan_edit->clear();
        break;
    case GROUP:
	group_label->setText("<h2>" + m.replace(QRegExp("Group      : "),"") + "</h2>");
	break;
    case VAR:
	if(m.contains("Last on")) {
	    state = LOGINNB;
	}
	break;
    case NAME:
	name_edit->setText("<h3>" + m.replace(QRegExp("Name       : "),"") + "</h3>");
	break;
    case EMAIL:
	email_edit->setText("<h3>" + m.replace(QRegExp("EMail      : "),"") + "</h3>");
	break;
    case FORMATION:
	formation_edit->setText("<h3>" + m.replace(QRegExp("Formation  : "),"") + "</h3>");
	break;
    case BIRTHDAY:
	birthday_edit->setText("<h3>" + m.replace(QRegExp("Birthday   : "),"") + "</h3>");
	break;
    case PLAN:
	if(m.contains("End of finger")) {
	    state = LOGIN;
	    repaint();
	}
	else {
	    if(!m.contains("Plan       :")) {
//		plan_edit->append(m.replace(QRegExp("^[^\\d]*"),""));
		plan_edit->append(m);		
	    }
	    state = PLAN;
	}
	break;
    default:
        break;
    }
}

void IdForm::init() {
    state = LOGIN;
}
