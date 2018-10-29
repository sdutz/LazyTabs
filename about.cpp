#include "about.h"
#include "ui_about.h"

//----------------------------------------------------------
About::About(QWidget *parent) : QDialog(parent), ui(new Ui::About)
{
    ui->setupUi(this) ;
    setWindowTitle( "About") ;

    ui->label->setAlignment( Qt::AlignCenter) ;
    ui->label->setText( PrePareInfo()) ;
}

//----------------------------------------------------------
About::~About()
{
    delete ui;
}

//----------------------------------------------------------
QString
About::PrePareInfo( void)
{
    QString szContents ;

    szContents = "Made by sdutz\n" ;
    szContents += "zambellilorenzo@gmail.com\n" ;
    szContents += "https://github.com/sdutz/LazyTabs\n\n" ;
    szContents += "Shorcuts list : \n" ;
    szContents += "Key a addchord\n" ;
    szContents += "Key c sendtoclip\n" ;
    szContents += "Key i insertchord\n" ;
    szContents += "Key l leftshift\n" ;
    szContents += "Key r rightshift\n" ;
    szContents += "Key z reset\n" ;
    szContents += "Key q exit\n" ;
    szContents += "Key s save\n" ;
    szContents += "Key o load\n" ;
    szContents += "Key t set focus to text area\n" ;
    szContents += "Key Escape set focus to  graphic area\n" ;
    szContents += "Key h help\n" ;

    return szContents ;
}
