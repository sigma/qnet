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
    DomUtil::writeEntry(*m_dom,"/filters/" + block_name->text() + "/result",block_result->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + block_name->text() + "/beginresult",block_begin_result->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + block_name->text() + "/endresult",block_end_result->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + block_name->text() + "/begin",block_begin->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + block_name->text() + "/end",block_end->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + block_name->text() + "/depend",block_input->text());
    DomUtil::writeBoolEntry(*m_dom,"/filters/" + block_name->text() + "/active",block_active_check->isChecked());
    DomUtil::writeIntEntry(*m_dom,"/filters/" + block_name->text() + "/policy",(block_subrules_check->isChecked())?0:1);
}


void MtpFiltersSettings::changedItem()
{
    DomUtil::writeEntry(*m_dom,"/filters/" + item_name->text() + "/result",item_result->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + item_name->text() + "/regexp",item_regexp->text());
    DomUtil::writeBoolEntry(*m_dom,"/filters/" + item_name->text() + "/active",item_active_check->isChecked());
}


void MtpFiltersSettings::changedGlobal()
{
    DomUtil::writeEntry(*m_dom,"/filters/" + global_name->text() + "/result",global_result->text());
    DomUtil::writeBoolEntry(*m_dom,"/filters/" + global_name->text() + "/active",global_active_check->isChecked());
    DomUtil::writeIntEntry(*m_dom,"/filters/" + global_name->text() + "/policy",(global_subrules_check->isChecked())?0:1);
}


void MtpFiltersSettings::changedLine()
{
    DomUtil::writeEntry(*m_dom,"/filters/" + line_name->text() + "/result",line_result->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + line_name->text() + "/regexp",line_regexp->text());
    DomUtil::writeBoolEntry(*m_dom,"/filters/" + line_name->text() + "/active",line_active_check->isChecked());
    DomUtil::writeIntEntry(*m_dom,"/filters/" + line_name->text() + "/policy",(line_subrules_check->isChecked())?0:1);
}


void MtpFiltersSettings::changedInput()
{
    DomUtil::writeEntry(*m_dom,"/filters/" + input_name->text() + "/result",input_result->text());
    DomUtil::writeEntry(*m_dom,"/filters/" + input_name->text() + "/regexp",input_regexp->text());
    DomUtil::writeBoolEntry(*m_dom,"/filters/" + input_name->text() + "/active",input_active_check->isChecked());
}

#define RULENAME(txt) (QInputDialog::getText("Rule name","Enter a name",QLineEdit::Normal,(txt)))

void MtpFiltersSettings::addGlobal()
{
    global_rules->insertItem(RULENAME("globalRule"));
    global_rules->setSelected(global_rules->count()-1,true);
    changedGlobal();
    updateList(global_rules,"/general/filters/global"); 
}


void MtpFiltersSettings::addBlock()
{
    block_rules->insertItem(RULENAME("blockRule"));
    block_rules->setSelected(block_rules->count()-1,true);
    changedBlock();
    updateList(block_rules,"/general/filters/block");
}


void MtpFiltersSettings::addLine()
{
    line_rules->insertItem(RULENAME("lineRule"));
    line_rules->setSelected(line_rules->count()-1,true);
    changedLine();
    updateList(line_rules,"/general/filters/line");
}


void MtpFiltersSettings::addItem()
{
    item_rules->insertItem(RULENAME("itemRule"));
    item_rules->setSelected(item_rules->count()-1,true);
    changedItem();
    updateList(item_rules,"/general/filters/item");
}


void MtpFiltersSettings::addInput()
{
    input_rules->insertItem(RULENAME("inputRule"));
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


void MtpFiltersSettings::activateGlobal(int index)
{
    if(modified_global) {
        changedGlobal();
        modified_global = false;
    }
    disconnect(global_result, SIGNAL(textChanged()), this, SLOT(slotGlobal()));
    disconnect(global_active_check, SIGNAL(toggled(bool)), this, SLOT(slotGlobal()));
    disconnect(global_subrules_check, SIGNAL(toggled(bool)), this, SLOT(slotGlobal()));
    displayGlobal(global_rules->text(index));
    connect(global_result, SIGNAL(textChanged()), SLOT(slotGlobal()));
    connect(global_active_check, SIGNAL(toggled(bool)), SLOT(slotGlobal()));
    connect(global_subrules_check, SIGNAL(toggled(bool)), SLOT(slotGlobal()));
}


void MtpFiltersSettings::activateBlock(int index )
{
    if(modified_block) {
        changedBlock();
        modified_block = false;
    }
    disconnect(block_begin, SIGNAL(textChanged(const QString &)), this, SLOT(slotBlock()));
    disconnect(block_end, SIGNAL(textChanged(const QString &)), this, SLOT(slotBlock()));    
    disconnect(block_input, SIGNAL(textChanged(const QString &)), this, SLOT(slotBlock()));
    disconnect(block_begin_result, SIGNAL(textChanged()), this, SLOT(slotBlock()));
    disconnect(block_end_result, SIGNAL(textChanged()), this, SLOT(slotBlock()));
    disconnect(block_result, SIGNAL(textChanged()), this, SLOT(slotBlock()));
    disconnect(block_active_check, SIGNAL(toggled(bool)), this, SLOT(slotBlock()));
    disconnect(block_subrules_check, SIGNAL(toggled(bool)), this, SLOT(slotBlock()));
    displayBlock(block_rules->text(index));
    connect(block_begin, SIGNAL(textChanged(const QString &)), SLOT(slotBlock()));
    connect(block_end, SIGNAL(textChanged(const QString &)), SLOT(slotBlock()));    
    connect(block_input, SIGNAL(textChanged(const QString &)), SLOT(slotBlock()));
    connect(block_begin_result, SIGNAL(textChanged()), SLOT(slotBlock()));
    connect(block_end_result, SIGNAL(textChanged()), SLOT(slotBlock()));
    connect(block_result, SIGNAL(textChanged()), SLOT(slotBlock()));
    connect(block_active_check, SIGNAL(toggled(bool)), this, SLOT(slotBlock()));
    connect(block_subrules_check, SIGNAL(toggled(bool)), this, SLOT(slotBlock()));
}


void MtpFiltersSettings::activateLine(int  index )
{
    if(modified_line) {
        changedLine();
        modified_line = false;
    }
    disconnect(line_regexp, SIGNAL(textChanged(const QString &)), this, SLOT(slotLine()));
    disconnect(line_result, SIGNAL(textChanged()), this, SLOT(slotLine()));
    disconnect(line_active_check, SIGNAL(toggled(bool)), this, SLOT(slotLine()));
    disconnect(line_subrules_check, SIGNAL(toggled(bool)), this, SLOT(slotLine()));
    displayLine(line_rules->text(index));
    connect(line_regexp, SIGNAL(textChanged(const QString &)), SLOT(slotLine()));
    connect(line_result, SIGNAL(textChanged()), SLOT(slotLine()));
    connect(line_active_check, SIGNAL(toggled(bool)), this, SLOT(slotLine()));
    connect(line_subrules_check, SIGNAL(toggled(bool)), this, SLOT(slotLine()));
}


void MtpFiltersSettings::activateItem(int index )
{
    if(modified_item) {
        changedItem();
        modified_item = false;
    }
    disconnect(item_regexp, SIGNAL(textChanged(const QString &)), this, SLOT(slotItem()));
    disconnect(item_result, SIGNAL(textChanged()), this, SLOT(slotItem()));
    disconnect(item_active_check, SIGNAL(toggled(bool)), this, SLOT(slotItem()));
    displayItem(item_rules->text(index));
    connect(item_regexp, SIGNAL(textChanged(const QString &)), SLOT(slotItem()));
    connect(item_result, SIGNAL(textChanged()), SLOT(slotItem()));
    connect(item_active_check, SIGNAL(toggled(bool)), this, SLOT(slotItem()));
}


void MtpFiltersSettings::activateInput(int index)
{
    if(modified_input) {
        changedInput();
        modified_input = false;
    }
    disconnect(input_regexp, SIGNAL(textChanged(const QString &)), this, SLOT(slotInput()));
    disconnect(input_result, SIGNAL(textChanged()), this, SLOT(slotInput()));
    disconnect(input_active_check, SIGNAL(toggled(bool)), this, SLOT(slotInput()));
    displayInput(input_rules->text(index));
    connect(input_regexp, SIGNAL(textChanged(const QString &)), SLOT(slotInput()));
    connect(input_result, SIGNAL(textChanged()), SLOT(slotInput()));
    connect(input_active_check, SIGNAL(toggled(bool)), this, SLOT(slotInput()));
}


void MtpFiltersSettings::init()
{
    modified_global = modified_block = modified_line = modified_item = modified_input = false;
}


void MtpFiltersSettings::destroy()
{
}


void MtpFiltersSettings::slotGlobal()
{
    modified_global = true;
    disconnect(global_result, SIGNAL(textChanged()), this, SLOT(slotGlobal()));
}


void MtpFiltersSettings::slotBlock()
{
    modified_block = true;
    disconnect(block_begin, SIGNAL(textChanged(const QString &)), this, SLOT(slotBlock()));
    disconnect(block_end, SIGNAL(textChanged(const QString &)), this, SLOT(slotBlock()));    
    disconnect(block_input, SIGNAL(textChanged(const QString &)), this, SLOT(slotBlock()));
    disconnect(block_begin_result, SIGNAL(textChanged()), this, SLOT(slotBlock()));
    disconnect(block_end_result, SIGNAL(textChanged()), this, SLOT(slotBlock()));
    disconnect(block_result, SIGNAL(textChanged()), this, SLOT(slotBlock()));
}


void MtpFiltersSettings::slotLine()
{
    modified_line = true;
    disconnect(line_regexp, SIGNAL(textChanged(const QString &)), this, SLOT(slotLine()));
    disconnect(line_result, SIGNAL(textChanged()), this, SLOT(slotLine()));
}


void MtpFiltersSettings::slotItem()
{
    modified_item = true;
    disconnect(item_regexp, SIGNAL(textChanged(const QString &)), this, SLOT(slotItem()));
    disconnect(item_result, SIGNAL(textChanged()), this, SLOT(slotItem()));
}


void MtpFiltersSettings::slotInput()
{
    modified_input = true;
    disconnect(input_regexp, SIGNAL(textChanged(const QString &)), this, SLOT(slotInput()));
    disconnect(input_result, SIGNAL(textChanged()), this, SLOT(slotInput()));
}


void MtpFiltersSettings::apply()
{
    if(modified_global) changedGlobal();
    if(modified_block) changedBlock();
    if(modified_line) changedLine();
    if(modified_item) changedItem();
    if(modified_input) changedInput();
}
