/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include "domutil.h"

void MtpFiltersSettings::displayGlobal( const QString & name)
{
    global_name->setText(name);
    global_result->setText(DomUtil::readEntry(*m_dom,"/filters/" + name + "/result"));
    global_active_check->setChecked(DomUtil::readBoolEntry(*m_dom,"/filters/" + name + "/active"));
    global_subrules_check->setChecked(!DomUtil::readIntEntry(*m_dom,"/filters/" + name + "/policy"));    
}


void MtpFiltersSettings::displayBlock( const QString & name)
{
    block_name->setText(name);
    block_result->setText(DomUtil::readEntry(*m_dom,"/filters/" + name + "/result"));
    block_begin_result->setText(DomUtil::readEntry(*m_dom,"/filters/" + name + "/beginresult"));
    block_end_result->setText(DomUtil::readEntry(*m_dom,"/filters/" + name + "/endresult"));
    block_begin->setText(DomUtil::readEntry(*m_dom,"/filters/" + name + "/begin"));
    block_end->setText(DomUtil::readEntry(*m_dom,"/filters/" + name + "/end"));
    block_input->setText(DomUtil::readEntry(*m_dom,"/filters/" + name + "/depend",""));
    block_active_check->setChecked(DomUtil::readBoolEntry(*m_dom,"/filters/" + name + "/active"));
    block_subrules_check->setChecked(!DomUtil::readIntEntry(*m_dom,"/filters/" + name + "/policy"));
}


void MtpFiltersSettings::displayLine( const QString & name)
{
    line_name->setText(name);
    line_result->setText(DomUtil::readEntry(*m_dom,"/filters/" + name + "/result"));
    line_regexp->setText(DomUtil::readEntry(*m_dom,"/filters/" + name + "/regexp"));
    line_active_check->setChecked(DomUtil::readBoolEntry(*m_dom,"/filters/" + name + "/active"));
    line_subrules_check->setChecked(!DomUtil::readIntEntry(*m_dom,"/filters/" + name + "/policy"));
}


void MtpFiltersSettings::displayItem( const QString & name)
{
    item_name->setText(name);
    item_result->setText(DomUtil::readEntry(*m_dom,"/filters/" + name + "/result"));
    item_regexp->setText(DomUtil::readEntry(*m_dom,"/filters/" + name + "/regexp"));
    item_active_check->setChecked(DomUtil::readBoolEntry(*m_dom,"/filters/" + name + "/active"));
}


void MtpFiltersSettings::displayInput( const QString & name)
{
    input_name->setText(name);
    input_result->setText(DomUtil::readEntry(*m_dom,"/filters/" + name + "/result"));
    input_regexp->setText(DomUtil::readEntry(*m_dom,"/filters/" + name + "/regexp"));
    input_active_check->setChecked(DomUtil::readBoolEntry(*m_dom,"/filters/" + name + "/active"));
}


void MtpFiltersSettings::setDom( QDomDocument * dom)
{
    global_rules->insertStringList(DomUtil::readListEntry(*dom,"/general/filters/global","filter"));
    block_rules->insertStringList(DomUtil::readListEntry(*dom,"/general/filters/block","filter"));
    line_rules->insertStringList(DomUtil::readListEntry(*dom,"/general/filters/line","filter"));
    item_rules->insertStringList(DomUtil::readListEntry(*dom,"/general/filters/item","filter"));
    input_rules->insertStringList(DomUtil::readListEntry(*dom,"/general/filters/input","filter"));
    m_dom = dom;
}




void MtpFiltersSettings::changedBlock()
{
    DomUtil::writeEntry(*m_dom,"/filters/" + block_rules->currentText() + "/result",block_result->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + block_rules->currentText() + "/beginresult",block_begin_result->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + block_rules->currentText() + "/endresult",block_end_result->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + block_rules->currentText() + "/begin",block_begin->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + block_rules->currentText() + "/end",block_end->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + block_rules->currentText() + "/depend",block_input->text());
    DomUtil::writeBoolEntry(*m_dom,"/filters/" + block_rules->currentText() + "/active",block_active_check->isChecked());
    DomUtil::writeIntEntry(*m_dom,"/filters/" + block_rules->currentText() + "/policy",(block_subrules_check->isChecked())?0:1);
}


void MtpFiltersSettings::changedItem()
{
    DomUtil::writeEntry(*m_dom,"/filters/" + item_rules->currentText() + "/result",item_result->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + item_rules->currentText() + "/regexp",item_regexp->text());
    DomUtil::writeBoolEntry(*m_dom,"/filters/" + item_rules->currentText() + "/active",item_active_check->isChecked());
}


void MtpFiltersSettings::changedGlobal()
{
    DomUtil::writeEntry(*m_dom,"/filters/" + global_rules->currentText() + "/result",global_result->text());
    DomUtil::writeBoolEntry(*m_dom,"/filters/" + global_rules->currentText() + "/active",global_active_check->isChecked());
    DomUtil::writeIntEntry(*m_dom,"/filters/" + global_rules->currentText() + "/policy",(global_subrules_check->isChecked())?0:1);
}


void MtpFiltersSettings::changedLine()
{
    DomUtil::writeEntry(*m_dom,"/filters/" + line_rules->currentText() + "/result",line_result->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + line_rules->currentText() + "/regexp",line_regexp->text());
    DomUtil::writeBoolEntry(*m_dom,"/filters/" + line_rules->currentText() + "/active",line_active_check->isChecked());
    DomUtil::writeIntEntry(*m_dom,"/filters/" + line_rules->currentText() + "/policy",(line_subrules_check->isChecked())?0:1);
}


void MtpFiltersSettings::changedInput()
{
    DomUtil::writeEntry(*m_dom,"/filters/" + input_rules->currentText() + "/result",input_result->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + input_rules->currentText() + "/regexp",input_regexp->text());
    DomUtil::writeBoolEntry(*m_dom,"/filters/" + input_rules->currentText() + "/active",input_active_check->isChecked());
}


void MtpFiltersSettings::addGlobal()
{
    global_rules->insertItem(global_name->text());
    global_rules->setSelected(global_rules->count()-1,true);
    changedGlobal();
    updateList(global_rules,"/general/filters/global"); 
}


void MtpFiltersSettings::addBlock()
{
    block_rules->insertItem(block_name->text());
    block_rules->setSelected(block_rules->count()-1,true);
    changedBlock();
    updateList(block_rules,"/general/filters/block");
}


void MtpFiltersSettings::addLine()
{
    line_rules->insertItem(line_name->text());
    line_rules->setSelected(line_rules->count()-1,true);
    changedLine();
    updateList(line_rules,"/general/filters/line");
}


void MtpFiltersSettings::addItem()
{
    item_rules->insertItem(item_name->text());
    item_rules->setSelected(item_rules->count()-1,true);
    changedItem();
    updateList(item_rules,"/general/filters/item");
}


void MtpFiltersSettings::addInput()
{
    input_rules->insertItem(input_name->text());
    input_rules->setSelected(input_rules->count()-1,true);
    changedInput();
    updateList(input_rules,"/general/filters/input");
}


void MtpFiltersSettings::delGlobal()
{
    QString name(global_rules->currentText());
    global_rules->removeItem(global_rules->currentItem());
    QDomElement child = DomUtil::elementByPath(*m_dom,"/filters/" + name);
    if(!child.isNull()) child.parentNode().removeChild(child);
    updateList(global_rules,"/general/filters/global");
}


void MtpFiltersSettings::delBlock()
{
    QString name(block_rules->currentText());
    block_rules->removeItem(block_rules->currentItem());
    QDomElement child = DomUtil::elementByPath(*m_dom,"/filters/" + name);
    if(!child.isNull()) child.parentNode().removeChild(child);
    updateList(block_rules,"/general/filters/block");
}


void MtpFiltersSettings::delLine()
{
    QString name(line_rules->currentText());
    line_rules->removeItem(line_rules->currentItem());
    QDomElement child = DomUtil::elementByPath(*m_dom,"/filters/" + name);
    if(!child.isNull()) child.parentNode().removeChild(child);
    updateList(line_rules,"/general/filters/line");
}


void MtpFiltersSettings::delItem()
{
    QString name(item_rules->currentText());
    item_rules->removeItem(item_rules->currentItem());
    QDomElement child = DomUtil::elementByPath(*m_dom,"/filters/" + name);
    if(!child.isNull()) child.parentNode().removeChild(child);
    updateList(item_rules,"/general/filters/item");
}


void MtpFiltersSettings::delInput()
{
    QString name(input_rules->currentText());
    input_rules->removeItem(input_rules->currentItem());
    QDomElement child = DomUtil::elementByPath(*m_dom,"/filters/" + name);
    if(!child.isNull()) child.parentNode().removeChild(child);
    updateList(input_rules,"/general/filters/input");
}


void MtpFiltersSettings::updateList( QListBox *box, const QString & path )
{
    QStringList l;
    for(uint i = 0; i<box->count(); i++) l << box->text(i);
    DomUtil::writeListEntry(*m_dom,path,"filter",l);
}


void MtpFiltersSettings::upGlobal()
{
    up(global_rules);
    updateList(global_rules,"/general/filters/global");
}


void MtpFiltersSettings::downGlobal()
{
    down(global_rules);
    updateList(global_rules,"/general/filters/global");
}


void MtpFiltersSettings::upBlock()
{
    up(block_rules);
    updateList(block_rules,"/general/filters/block");
}


void MtpFiltersSettings::downBlock()
{
    down(block_rules);
    updateList(block_rules,"/general/filters/block");
}


void MtpFiltersSettings::upLine()
{
    up(line_rules);
    updateList(line_rules,"/general/filters/line");
}


void MtpFiltersSettings::downLine()
{
    down(line_rules);
    updateList(line_rules,"/general/filters/line");
}


void MtpFiltersSettings::upItem()
{
    up(item_rules);
    updateList(item_rules,"/general/filters/item");
}


void MtpFiltersSettings::downItem()
{
    down(item_rules);
    updateList(item_rules,"/general/filters/item");
}


void MtpFiltersSettings::upInput()
{
    up(input_rules);
    updateList(input_rules,"/general/filters/input");
}


void MtpFiltersSettings::downInput()
{
    down(input_rules);
    updateList(input_rules,"/general/filters/input");
}


void MtpFiltersSettings::up( QListBox * box)
{
    int index = box->currentItem();
    if (index) {
	QString text = box->currentText();
	box->removeItem(index);
	box->insertItem(text,index - 1);
	box->setCurrentItem(index-1);
    }
}


void MtpFiltersSettings::down( QListBox * box)
{
    uint index = box->currentItem();

    if (index < box->count()) {
	QString text = box->currentText();
	box->removeItem(index);
	box->insertItem(text,index + 1);
	box->setCurrentItem(index+1);
    }
}
