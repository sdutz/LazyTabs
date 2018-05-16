#include "config.h"

//----------------------------------------------------------
config::config()
{
    m_szFretsKey   = "frets" ;
    m_szStringsKey = "strings" ;
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
config::SetValues( int nStrings, int nFrets)
{
    m_set.setValue( m_szFretsKey, nFrets);
    m_set.setValue( m_szStringsKey, nStrings);
}
