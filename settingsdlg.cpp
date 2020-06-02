#include "settingsdlg.h"
#include "ui_settingsdlg.h"
#include<QFileDialog>

//----------------------------------------------------------
settingsdlg::settingsdlg(QWidget *parent) : QDialog(parent), ui(new Ui::settingsdlg)
{
    int     nFrets ;
    int     nStrings ;
    QString szLang ;

    ui->setupUi(this);

    m_conf.GetValues( &nStrings, &nFrets) ;
    ui->fretsn->setValue( nFrets) ;
    ui->stringsn->setValue( nStrings) ;
    ui->langCmb->addItems( m_conf.GetLangList()) ;
    ui->langCmb->setCurrentText( m_conf.GetLang()) ;
    ui->dbEdit->setText( m_conf.GetDbFile()) ;
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
    m_conf.SetValues( ui->stringsn->value(), ui->fretsn->value(),
                      ui->langCmb->currentText(), ui->dbEdit->text(),
                      ui->darkUI->isChecked());
}

//----------------------------------------------------------
void
settingsdlg::on_dbBtn_clicked()
{
    ui->dbEdit->setText( QFileDialog::getOpenFileName( this, tr( "Select db file"), "", "*.txt")) ;
}
