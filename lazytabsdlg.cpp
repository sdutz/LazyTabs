#include "lazytabsdlg.h"
#include "ui_lazytabsdlg.h"
#include "settingsdlg.h"
#include "repeatdlg.h"
#include <QInputDialog>
#include <QKeyEvent>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTextBlock>
#include <about.h>

//----------------------------------------------------------
LazyTabsDlg::LazyTabsDlg( QWidget *parent) : QDialog(parent), ui( new Ui::LazyTabsDlg)
{
    bool    bDark ;
    QFont   font ;
    QColor  col ;

    ui->setupUi(this);
    col = palette().color( backgroundRole()) ;
    bDark = col.red() < 125  &&  col.green() < 125  &&  col.blue() < 125 ;
    m_pScene = new TabsScene( bDark, this) ;
    ui->tabsView->setScene( m_pScene) ;
    Init() ;
    SetLang( true) ;
    ui->tabsView->scale( 1.25, 1.25) ;
    font = ui->songTabs->font() ;
    font.setPointSize( font.pointSize() + 2) ;
    ui->songTabs->setFont( font) ;
    LoadPrj( m_conf.GetPrj()) ;
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
    QString szChord = m_pScene->GetChord() ;

    if ( QApplication::keyboardModifiers()  &  Qt::ShiftModifier) {
        ui->songTabs->moveCursor( QTextCursor::End) ;
    }

    if ( ! szChord.isEmpty()) {
        ui->songTabs->insertPlainText( szChord + "\n") ;
    }

    m_bMod = true ;
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
        on_newpr_clicked() ;
        SetLang( false);
    }
}

//----------------------------------------------------------
bool
LazyTabsDlg::Init( bool bFromFile)
{
    ui->songTabs->clear();
    ui->songTabs->setAlignment( Qt::AlignCenter) ;
    m_parser.initMaps( m_conf.GetDbFile()) ;

    int  nFrets ;
    int  nStrings ;
    m_conf.GetValues( nStrings, nFrets) ;
    m_pScene->SetData( nStrings, nFrets) ;
    if ( ! bFromFile) {
        if ( nStrings == 6) {
            ui->songTabs->insertPlainText( "E A D G B e \n\n");
        }
        else if ( nStrings == 4) {
            ui->songTabs->insertPlainText( "g C E A \n\n");
        }
    }

    bool bOk = m_pScene->Draw() ;
    m_bMod = false ;

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
    QString szFile = QCoreApplication::applicationName() + "_" + m_conf.GetLang() + ".qm" ;
    szFile.replace( " ", "") ;
    bool bOk = m_cLang.load( szFile, ":/tr") ;

    if ( bInit) {
        bOk &= QCoreApplication::installTranslator( &m_cLang) ;
    }

    return bOk ;
}

//----------------------------------------------------------
void
LazyTabsDlg::on_insertChord_clicked()
{
    bool         bOk ;
    QInputDialog cInput ;
    cInput.setInputMode( QInputDialog::InputMode::TextInput) ;
    QString szVal = cInput.getText( this, tr("Type your chord"), tr("eg : D#+"), QLineEdit::Normal, "", &bOk) ;
    if ( ! bOk) {
        return ;
    }

    chordsMode   nMode ;
    int          nVal ;
    int          nStrings ;
    m_conf.GetValues( nStrings, nVal) ;
    if ( nStrings == 6) {
        nMode = chordsMode::GUITAR ;
    }
    else if ( nStrings == 4) {
        nMode = chordsMode::UKULELE ;
    }
    else {
        return ;
    }

    QVector<int> anVals ;
    if ( ! szVal.isEmpty()  &&  bOk  &&  m_parser.parse( szVal, nMode, &anVals)) {
        m_pScene->SetChord( anVals) ;
    }
}

//----------------------------------------------------------
void
LazyTabsDlg::keyPressEvent( QKeyEvent* pEvent)
{
    if ( pEvent == nullptr) {
        return ;
    }

    switch (pEvent->key()) {
        case Qt::Key_A:
            return on_addChord_clicked() ;
        case Qt::Key_C:
            return on_sendToClip_clicked() ;
        case Qt::Key_I:
            return on_insertChord_clicked() ;
        case Qt::Key_L:
            return on_leftShift_clicked() ;
        case Qt::Key_R:
            return on_rightShift_clicked() ;
        case Qt::Key_Z:
            return on_reset_clicked() ;
        case Qt::Key_Q:
            close() ;
            break ;
        case Qt::Key_S:
            return on_save_clicked() ;
        case Qt::Key_O:
            return on_load_clicked() ;
        case Qt::Key_Escape:
            ui->tabsView->setFocus() ;
            break ;
        case Qt::Key_T:
            ui->songTabs->setFocus() ;
            break ;
        case Qt::Key_H:
            return on_help_clicked() ;
        case Qt::Key_D:
            return on_delChord_clicked() ;
        case Qt::Key_F:
            return on_repeatChord_clicked();
    }
}

//----------------------------------------------------------
void
LazyTabsDlg::on_load_clicked()
{
    if ( m_bMod  &&  QMessageBox::question( this, tr("Save"), tr("Do you want to save your progress?"),
                                            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        on_save_clicked() ;
    }

    QString szDir = m_conf.GetPrj() ;
    szDir.truncate( szDir.lastIndexOf('/')) ;

    QString szFile = QFileDialog::getOpenFileName( this, tr( "Select project file"), szDir, "*.txt") ;

    LoadPrj( szFile) ;
}

//----------------------------------------------------------
bool
LazyTabsDlg::LoadPrj( const QString& szPrj)
{
    QStringList slVals ;
    if ( ! szPrj.isEmpty()  &&  m_parser.parseFile( szPrj, &slVals)) {
        QString szTuning = slVals[0].replace( " ", "") ;
        szTuning.remove("#") ;
        m_conf.SetStrings( szTuning.length()) ;
        Init( true) ;
        QVector<int>anVals ;
        m_parser.parse( slVals.last(), &anVals) ;
        m_pScene->SetChord( anVals) ;
        ui->songTabs->insertPlainText( slVals[0] + "\n\n") ;
        for ( int n = 1 ;  n < slVals.size() ;  n ++) {
            ui->songTabs->insertPlainText( slVals[n] + "\n") ;
        }

        m_conf.SetPrj( szPrj) ;
        QString szTitle = windowTitle() ;
        szTitle += " - " + szPrj ;
        setWindowTitle( szTitle) ;

        return true ;
    }

    return false ;
}

//----------------------------------------------------------
void
LazyTabsDlg::on_save_clicked()
{
    QString szFile = m_conf.GetPrj() ;
    if ( szFile.isEmpty()) {
        szFile = QFileDialog::getSaveFileName( this, tr( "Select project file"), "", "*.txt") ;
    }

    QFile file( szFile) ;
    if ( ! file.open( QIODevice::WriteOnly | QIODevice::Text)) {
        return ;
    }

    QTextStream stream( &file) ;
    stream<< ui->songTabs->toPlainText() ;
    file.close() ;
    m_conf.SetPrj( szFile) ;
    m_bMod = false ;
}

//----------------------------------------------------------
void
LazyTabsDlg::closeEvent( QCloseEvent* pEvent)
{
    if ( pEvent == nullptr) {
        return ;
    }

    if ( ! m_bMod) {
        pEvent->accept();
    }
    else {
        int nRet = QMessageBox::question( this, tr("Save"), tr("Do you want to save your progress?"),
                                          QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel) ;
        switch ( nRet) {
            case QMessageBox::Cancel :
                pEvent->ignore() ;
            break ;
            case QMessageBox::Yes :
                on_save_clicked() ;
                pEvent->accept() ;
            break ;
            case QMessageBox::No :
                pEvent->accept() ;
            break ;
        }
    }
}

//----------------------------------------------------------
void
LazyTabsDlg::on_help_clicked()
{
    About about(this) ;

    about.exec() ;
}

//----------------------------------------------------------
void
LazyTabsDlg::on_newpr_clicked()
{
    if ( m_bMod  &&  QMessageBox::question( this, tr("Save"), tr("Do you want to save your progress?"),
                                            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        on_save_clicked() ;
    }

    Init() ;

    m_conf.SetPrj( "") ;
    QString szTitle = windowTitle() ;
    int nPos = szTitle.indexOf('-') ;
    if ( nPos > 0) {
        szTitle.truncate( nPos - 1) ;
        setWindowTitle( szTitle) ;
    }
}

//----------------------------------------------------------
void
LazyTabsDlg::on_delChord_clicked()
{
    ui->songTabs->setFocus() ;
    ui->songTabs->moveCursor( QTextCursor::End) ;
    ui->songTabs->moveCursor( QTextCursor::PreviousCharacter) ;
    ui->songTabs->moveCursor( QTextCursor::StartOfLine, QTextCursor::KeepAnchor) ;
    ui->songTabs->textCursor().removeSelectedText() ;
    ui->songTabs->textCursor().deletePreviousChar() ;
    ui->songTabs->moveCursor( QTextCursor::End) ;

    m_bMod = true ;
}

//----------------------------------------------------------
void LazyTabsDlg::on_repeatChord_clicked()
{

    RepeatDlg rDlg(this) ;
    if (rDlg.exec() == QDialog::Accepted) {
        int nStart, nChords, nCount = 0 ;
        rDlg.getRes( nStart, nChords, nCount) ;

        QStringList lszChords = ui->songTabs->toPlainText().split("\n") ;

        for (int i = 0 ; i < nCount ; i ++) {

            for (int j = 0 ; j < nChords ; j ++ ) {
                ui->songTabs->insertPlainText(lszChords.at(lszChords.size()-nStart-1+j) + "\n") ;
            }
        }

        ui->songTabs->moveCursor( QTextCursor::End) ;

        m_bMod = true ;
    }

}

//----------------------------------------------------------
void
LazyTabsDlg::on_songTabs_cursorPositionChanged()
{
    QString szRow = ui->songTabs->textCursor().block().text() ;

    if ( szRow.isEmpty()  ||  m_szCurrRow == szRow) {
        return ;
    }

    QVector<int> anVals ;
    if (  m_parser.parse( szRow, &anVals)) {
        m_pScene->SetChord( anVals) ;
    }

    m_szCurrRow = szRow ;
}

