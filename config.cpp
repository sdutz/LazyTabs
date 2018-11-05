#include "config.h"

//----------------------------------------------------------
config::config()
{
    m_szLangKey    = "lang" ;
    m_szFretsKey   = "frets" ;
    m_szStringsKey = "strings" ;
    m_szDbFileKey  = "dbfile" ;
    m_szPrjKey     = "prj" ;
}


//----------------------------------------------------------
QString
config::GetPrj( void)
{
    return m_set.value( m_szPrjKey, "").toString() ;
}

//----------------------------------------------------------
QString
config::GetDbFile( void)
{
    return m_set.value( m_szDbFileKey, "db.txt").toString() ;
}

//----------------------------------------------------------
QString
config::GetLang( void)
{
    return m_set.value( m_szLangKey, "eng").toString() ;
}

//----------------------------------------------------------
void
config::GetValues( int* pnStrings, int* pnFrets)
{
    if ( pnStrings == nullptr  ||  pnFrets == nullptr) {
         return ;
    }

    *pnFrets   = m_set.value( m_szFretsKey, 14).toInt() ;
    *pnStrings = m_set.value( m_szStringsKey, 6).toInt() ;
}

//----------------------------------------------------------
void
config::SetValues( int nStrings, int nFrets, const QString& szLang, const QString& szDBFile)
{
    m_set.setValue( m_szLangKey, szLang) ;
    m_set.setValue( m_szFretsKey, nFrets) ;
    m_set.setValue( m_szStringsKey, nStrings) ;
    m_set.setValue( m_szDbFileKey, szDBFile) ;
}

//----------------------------------------------------------
void
config::SetStrings( int nStrings)
{
    m_set.setValue( m_szStringsKey, nStrings) ;
}

//----------------------------------------------------------
void
config::SetPrj( const QString& szPrj)
{
    m_set.setValue( m_szPrjKey, szPrj) ;
}

//----------------------------------------------------------
QStringList
config::GetLangList( void)
{
    QStringList lszLangs ;

    lszLangs.append("en");
    lszLangs.append("it");

    return lszLangs ;
}
