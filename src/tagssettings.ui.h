/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <qfontdatabase.h>
#include <qcheckbox.h>
#include <qspinbox.h>
#include <qcolordialog.h>
#include <qinputdialog.h>

void TagsSettings::init() {
    m_db = new QFontDatabase;
    default_size = this->font().pointSize();
    comboFontFamily->insertStringList(m_db->families());
    slotSelectFamily();
    slotUpdatePreview();
}

void TagsSettings::destroy() {
    delete m_db;
}

void TagsSettings::addTagItem(TagItem & it) {
    map.insert(it.name,it);
    tags_box->insertItem(it.name);
}

void TagsSettings::delTagItem(const QString& name) {
    map.remove(name);
}

void TagsSettings::slotUpdateInfo(const QString & name) {
    TagItem it = *(map.find(name));
    nameEdit->setText(it.name);
    comboFontFamily->setCurrentText(it.family);
    comboFontStyle->setCurrentText(it.style);
    editPreview->setPaletteForegroundColor(it.color);
    checkStrikeout->setChecked(it.strike);
    checkUnderline->setChecked(it.underline);
    checkSpaces->setChecked(it.collapse);
    spinFontSize->setValue(it.size);
    slotUpdatePreview();
}

void TagsSettings::slotSelectFamily()
{
    comboFontStyle->clear();
    comboFontStyle->insertStringList(m_db->styles(comboFontFamily->currentText()));
}

void TagsSettings::slotUpdatePreview()
{
    QFont font( comboFontFamily->currentText(), default_size + ( spinFontSize->value() - 3) );
    font.setUnderline( checkUnderline->isChecked() );
    font.setStrikeOut( checkStrikeout->isChecked() );
    font.setBold( m_db->bold( comboFontFamily->currentText(), comboFontStyle->currentText()));
    font.setItalic( m_db->italic( comboFontFamily->currentText(), comboFontStyle->currentText()));
    editPreview->setFont( font );

    TagItem it(nameEdit->text(), comboFontFamily->currentText(), comboFontStyle->currentText(), editPreview->paletteForegroundColor().rgb(),
               checkStrikeout->isChecked(), checkUnderline->isChecked(), checkSpaces->isChecked(), spinFontSize->value());
    map[nameEdit->text()]=it;
}

void TagsSettings::slotSelectColor()
{
    QColor color = QColorDialog::getColor(textLabel2_2->paletteBackgroundColor());
    editPreview->setPaletteForegroundColor(color);
    map[nameEdit->text()].color = color.rgb();
}

#define TAGNAME(txt) (QInputDialog::getText("Tag name","Enter a name",QLineEdit::Normal,(txt),&ok,this))

void TagsSettings::addTag()
{
    bool ok;
    QString name = TAGNAME("tag");
    if(ok) {
        tags_box->insertItem(name);
        tags_box->setSelected(tags_box->count()-1,true);
        map[name]=TagItem(name);
        slotUpdateInfo(name);
    }
}

void TagsSettings::delTag()
{
    tags_box->removeItem(tags_box->currentItem());
}

void TagsSettings::up()
{
    int index = tags_box->currentItem();
    if (index) {
	QString text = tags_box->currentText();
	tags_box->removeItem(index);
	tags_box->insertItem(text,index - 1);
	tags_box->setCurrentItem(index-1);
    }
}


void TagsSettings::down()
{
    uint index = tags_box->currentItem();

    if (index < tags_box->count()) {
	QString text = tags_box->currentText();
	tags_box->removeItem(index);
	tags_box->insertItem(text,index + 1);
	tags_box->setCurrentItem(index+1);
    }
}
