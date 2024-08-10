#include "repeatdlg.h"
#include "ui_repeatdlg.h"

//----------------------------------------------------------
RepeatDlg::RepeatDlg(QWidget *parent) : QDialog(parent), ui(new Ui::RepeatDlg)
{
    ui->setupUi(this);
}

//----------------------------------------------------------
RepeatDlg::~RepeatDlg()
{
    delete ui;
}

//----------------------------------------------------------
void
RepeatDlg::getRes(int& nStart, int& nChords, int& nCount)
{
    nStart = ui->startn->value() ;
    nChords = ui->chordsn->value() ;
    nCount = ui->countn->value() ;
}
