#include "config.h"

//----------------------------------------------------------
config::config()
{
    m_szLangKey    = "lang" ;
    m_szFretsKey   = "frets" ;
    m_szStringsKey = "strings" ;
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
    if ( pnStrings == NULL  ||  pnFrets == NULL) {
         return ;
    }

    *pnFrets   = m_set.value( m_szFretsKey, 14).toInt() ;
    *pnStrings = m_set.value( m_szStringsKey, 6).toInt() ;
}

//----------------------------------------------------------
void
config::SetValues( int nStrings, int nFrets, const QString& szLang)
{
    m_set.setValue( m_szLangKey, szLang) ;
    m_set.setValue( m_szFretsKey, nFrets) ;
    m_set.setValue( m_szStringsKey, nStrings) ;
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
