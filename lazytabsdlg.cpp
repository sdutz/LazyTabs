#include "lazytabsdlg.h"
#include "ui_lazytabsdlg.h"
#include "settingsdlg.h"

//----------------------------------------------------------
LazyTabsDlg::LazyTabsDlg(QWidget *parent) : QDialog(parent), ui(new Ui::LazyTabsDlg)
{
    QFont font ;

    ui->setupUi(this);
    m_pScene = new TabsScene( this) ;
    ui->tabsView->setScene( m_pScene);
    Init() ;
    SetLang( true) ;
    ui->tabsView->scale( 1.25, 1.25) ;
    font = ui->songTabs->font() ;
    font.setPointSize( font.pointSize() + 2) ;
    ui->songTabs->setFont( font);
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
        SetLang( false);
    }
}

//----------------------------------------------------------
bool
LazyTabsDlg::Init( void)
{
    bool bOk ;
    int  nFrets ;
    int  nStrings ;

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

//----------------------------------------------------------
bool
LazyTabsDlg::SetLang( bool bInit)
{
    bool    bOk ;
    QString szFile ;

    szFile = QCoreApplication::applicationName() + "_" + m_conf.GetLang() + ".qm" ;
    szFile.replace( " ", "") ;
    bOk = m_cLang.load( szFile, ":/tr") ;

    if ( bInit) {
        bOk = bOk  &&  QCoreApplication::installTranslator( &m_cLang) ;
    }

    return bOk ;
}
