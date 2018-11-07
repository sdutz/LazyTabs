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
    bool         bGoOn ;
    int          nCurr ;
    int          nCount ;
    QString      szContents ;
    QVector<int> anUsed ;


    szContents = "Made by sdutz\n" ;
    szContents += "zambellilorenzo@gmail.com\n" ;
    szContents += "https://github.com/sdutz/LazyTabs\n\n" ;
    szContents += "Shorcuts list : \n" ;

    nCount = m_lszShortCuts.count() ;

    for ( int n = 0 ;  n < nCount ;  n ++) {
        bGoOn = true ;
        while ( bGoOn) {
            nCurr = qrand() % nCount ;
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
    m_lszShortCuts.append( "Key a addchord\n") ;
    m_lszShortCuts.append( "Key c sendtoclip\n") ;
    m_lszShortCuts.append( "Key i insertchord\n") ;
    m_lszShortCuts.append( "Key l leftshift\n") ;
    m_lszShortCuts.append( "Key r rightshift\n") ;
    m_lszShortCuts.append( "Key z reset\n") ;
    m_lszShortCuts.append( "Key q exit\n") ;
    m_lszShortCuts.append( "Key s save\n") ;
    m_lszShortCuts.append( "Key o load\n") ;
    m_lszShortCuts.append( "Key t set focus to text area\n") ;
    m_lszShortCuts.append( "Key Escape set focus to  graphic area\n") ;
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
