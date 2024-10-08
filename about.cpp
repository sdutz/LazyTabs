#include "about.h"
#include "ui_about.h"

//----------------------------------------------------------
About::About(QWidget *parent) : QDialog(parent), ui(new Ui::About)
{
    ui->setupUi(this) ;
    setWindowTitle( "About") ;

    ui->label->setAlignment( Qt::AlignCenter) ;
    FillShortCutsList() ;
    ui->label->setText( GetInfo()) ;
}

//----------------------------------------------------------
About::~About()
{
    delete ui;
}

//----------------------------------------------------------
QString
About::GetInfo( void)
{
    QVector<int> anUsed ;

    QString szContents =  "Made by sdutz\n" ;
    szContents += "zambellilorenzo@gmail.com\n" ;
    szContents += "https://github.com/sdutz/LazyTabs\n\n" ;
    szContents += "Shorcuts list : \n\n" ;

    int nCount = m_lszShortCuts.count() ;

    for ( int n = 0 ;  n < nCount ;  n ++) {
        bool bGoOn = true ;
        while ( bGoOn) {
            int nCurr = rand() % nCount ;
            if ( ! anUsed.contains( nCurr)) {
                bGoOn = false ;
                szContents += m_lszShortCuts[nCurr] ;
                anUsed.append( nCurr) ;
            }
        }
    }

    return szContents ;
}

//----------------------------------------------------------
void
About::FillShortCutsList( void)
{
    m_lszShortCuts.append( "Key a add chord\n") ;
    m_lszShortCuts.append( "Key d remove last chord\n") ;
    m_lszShortCuts.append( "Key c send to clip\n") ;
    m_lszShortCuts.append( "Key i insert chord\n") ;
    m_lszShortCuts.append( "Key l left shift\n") ;
    m_lszShortCuts.append( "Key r right shift\n") ;
    m_lszShortCuts.append( "Key z reset\n") ;
    m_lszShortCuts.append( "Key q exit\n") ;
    m_lszShortCuts.append( "Key s save\n") ;
    m_lszShortCuts.append( "Key o load\n") ;
    m_lszShortCuts.append( "Key t set focus to text area\n") ;
    m_lszShortCuts.append( "Key Escape set focus to  graphic area\n") ;
    m_lszShortCuts.append( "Key f repeat\n") ;
    m_lszShortCuts.append( "Key h help\n") ;
}

//----------------------------------------------------------
void
About::mousePressEvent( QMouseEvent* pEvent)
{
    if ( pEvent == nullptr) {
        return ;
    }

    ui->label->setText( GetInfo()) ;
}
