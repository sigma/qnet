/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <qfiledialog.h>

void PluginsSettings::slotAdd() {
    QStringList plugs = QFileDialog::getOpenFileNames("*.so",QString::null,this,"open files dialog",
						      "Select one or more files to open");
    plugins_box->insertStringList(plugs);
}

void PluginsSettings::slotDel() {
    plugins_box->removeItem(plugins_box->currentItem());
}
