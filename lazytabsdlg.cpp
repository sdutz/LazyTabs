#include "lazytabsdlg.h"
#include "ui_lazytabsdlg.h"

LazyTabsDlg::LazyTabsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LazyTabsDlg)
{
    ui->setupUi(this);
}

LazyTabsDlg::~LazyTabsDlg()
{
    delete ui;
}
