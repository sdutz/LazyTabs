#include "settingsdlg.h"
#include "ui_settingsdlg.h"

//----------------------------------------------------------
settingsdlg::settingsdlg(QWidget *parent) : QDialog(parent), ui(new Ui::settingsdlg)
{
    int     nFrets ;
    int     nStrings ;
    QString szLang ;

    ui->setupUi(this);

    m_conf.GetValues( &nStrings, &nFrets);
    ui->fretsn->setValue( nFrets);
    ui->stringsn->setValue( nStrings);
    ui->langCmb->addItems( m_conf.GetLangList());
    ui->langCmb->setCurrentText( m_conf.GetLang());
}

//----------------------------------------------------------
settingsdlg::~settingsdlg()
{
    delete ui;
}

//----------------------------------------------------------
void
settingsdlg::on_settingsdlg_accepted()
{
    m_conf.SetValues( ui->stringsn->value(), ui->fretsn->value(), ui->langCmb->currentText());
}

