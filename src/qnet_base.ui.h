/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/
#include "version.h"
#include <qmessagebox.h>

void QMtp_base::fileNew()
{

}

void QMtp_base::fileOpen()
{

}

void QMtp_base::fileSave()
{

}

void QMtp_base::fileSaveAs()
{

}

void QMtp_base::fileSessions()
{

}

void QMtp_base::fileExit()
{

}

void QMtp_base::editUndo()
{

}

void QMtp_base::editRedo()
{

}

void QMtp_base::editCut()
{

}

void QMtp_base::editCopy()
{

}

void QMtp_base::editPaste()
{

}

void QMtp_base::editFind()
{

}

void QMtp_base::helpIndex()
{

}

void QMtp_base::slotConfigure()
{

}

void QMtp_base::helpAbout()
{
    QMessageBox::about(this, "About QNet", CLIENT + QString("\n© 2002 - Sigma <Yann.Hodique@lifl.fr>"));
}

void QMtp_base::closeCurrentTab()
{

}

void QMtp_base::gotoNextTab()
{
    tabs->setCurrentPage((tabs->currentPageIndex() + 1) % tabs->count());
}

void QMtp_base::gotoPreviousTab()
{
    tabs->setCurrentPage((tabs->currentPageIndex() + tabs->count() - 1) % tabs->count());
}


void QMtp_base::slotDisplayFortune()
{

}


void QMtp_base::slotToggleMenu()
{
    if(menuBar()->isVisible())
	menuBar()->hide();
    else
	menuBar()->show();
}
