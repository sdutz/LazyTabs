#include "lazytabsdlg.h"
#include "ui_lazytabsdlg.h"

//----------------------------------------------------------
LazyTabsDlg::LazyTabsDlg(QWidget *parent) : QDialog(parent), ui(new Ui::LazyTabsDlg)
{
    ui->setupUi(this);
    m_pScene = new QGraphicsScene( this) ;
    ui->tabsView->setScene( m_pScene);
    m_cKey.Draw( m_pScene) ;
}

//----------------------------------------------------------
LazyTabsDlg::~LazyTabsDlg()
{
    delete ui;
}

//----------------------------------------------------------
bool
LazyTabsDlg::DrawKeyboard( void)
{

    return true ;
}
