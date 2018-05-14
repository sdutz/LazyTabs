#include "settingsdlg.h"
#include "ui_settingsdlg.h"

settingsdlg::settingsdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsdlg)
{
    ui->setupUi(this);
}

settingsdlg::~settingsdlg()
{
    delete ui;
}
