/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

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
}

void TagsSettings::slotSelectColor()
{
    QColor color = QColorDialog::getColor(textLabel2_2->paletteBackgroundColor());
    editPreview->setPaletteForegroundColor(color);
}
