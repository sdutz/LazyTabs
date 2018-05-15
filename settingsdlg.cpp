#include "settingsdlg.h"
#include "ui_settingsdlg.h"

//----------------------------------------------------------
settingsdlg::settingsdlg(QWidget *parent) : QDialog(parent), ui(new Ui::settingsdlg)
{
    int nFrets ;
    int nStrings ;

    ui->setupUi(this);

     m_conf.GetValues( &nStrings, &nFrets);
     ui->fretsn->setValue( nFrets);
     ui->stringsn->setValue( nStrings);
}

//----------------------------------------------------------
settingsdlg::~settingsdlg()
{
    delete ui;
}

//----------------------------------------------------------

void settingsdlg::on_settingsdlg_accepted()
{
    m_conf.SetValues( ui->stringsn->value(), ui->fretsn->value());
}
