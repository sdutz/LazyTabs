#include "lazytabsdlg.h"
#include "ui_lazytabsdlg.h"
#include "settingsdlg.h"


//----------------------------------------------------------
LazyTabsDlg::LazyTabsDlg(QWidget *parent) : QDialog(parent), ui(new Ui::LazyTabsDlg)
{
    ui->setupUi(this);
    m_pScene = new TabsScene( this) ;
    ui->tabsView->setScene( m_pScene);
    Init() ;
}

//----------------------------------------------------------
LazyTabsDlg::~LazyTabsDlg()
{
    delete ui;
}

//----------------------------------------------------------
void
LazyTabsDlg::on_addChord_clicked()
{
    ui->songTabs->insertPlainText( m_pScene->GetChord()) ;
}

//----------------------------------------------------------
void
LazyTabsDlg::on_sendToClip_clicked()
{
    ui->songTabs->selectAll();
    ui->songTabs->copy() ;
    ui->songTabs->moveCursor( QTextCursor::End);
}

//----------------------------------------------------------
void
LazyTabsDlg::on_config_clicked()
{
    settingsdlg setdlg( this) ;

    if ( setdlg.exec() == QDialog::Accepted) {
        Init() ;
    }
}

//----------------------------------------------------------
bool
LazyTabsDlg::Init()
{
    bool  bOk ;
    int   nFrets ;
    int   nStrings ;

    ui->songTabs->clear();
    m_conf.GetValues( &nStrings, &nFrets);
    m_pScene->SetData( nStrings, nFrets) ;
    if ( nStrings == 6) {
        ui->songTabs->insertPlainText( "E A D G B e \n\n");
    }
    else if ( nStrings == 4) {
        ui->songTabs->insertPlainText( "g C E A \n\n");
    }

    bOk = m_pScene->Draw() ;

    return bOk ;
}

//----------------------------------------------------------
void
LazyTabsDlg::on_leftShift_clicked()
{
    m_pScene->Move( true);
}

//----------------------------------------------------------
void
LazyTabsDlg::on_rightShift_clicked()
{
    m_pScene->Move( false);
}

//----------------------------------------------------------
void
LazyTabsDlg::on_reset_clicked()
{
    m_pScene->Reset();
}
