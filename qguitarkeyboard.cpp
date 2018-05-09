#include "qguitarkeyboard.h"

//----------------------------------------------------------
QGuitarKeyboard::QGuitarKeyboard()
{
    Init() ;
}

//----------------------------------------------------------
void
QGuitarKeyboard::Init()
{
    int nPos = 0 ;
    int nInc = 50 ;
    for ( int n = 0 ;  n <= 13 ;  n ++) {
        m_anFrets.append( nPos);
        nPos += nInc ;
        nInc -= 3 ;
    }

    for ( int n = 0 ;  n <= 50 ;  n += 10) {
        m_anStrings.append( n);
    }
}

//----------------------------------------------------------
bool
QGuitarKeyboard::Draw( QGraphicsScene* pScene)
{
    if ( pScene == NULL) {
        return false ;
    }

    foreach (int n, m_anFrets) {
        pScene->addLine(n, m_anStrings.first(), n, m_anStrings.last());
    }

    foreach (int n, m_anStrings) {
        pScene->addLine(m_anFrets.first(), n, m_anFrets.last(), n) ;
    }

    return true ;
}
