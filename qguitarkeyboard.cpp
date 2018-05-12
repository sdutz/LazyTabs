#include "qguitarkeyboard.h"

//----------------------------------------------------------
QGuitarKeyboard::QGuitarKeyboard()
{
    m_nFrets     = 13 ;
    m_nStrings   = 6 ;
    m_nFretDst   = 50 ;
    m_nStringDst = 10 ;

    Init() ;
}

//----------------------------------------------------------
QGuitarKeyboard::QGuitarKeyboard( int nStrings, int nFrets, int nStringDst, int nFretsDst)
{
    m_nFrets     = nFrets ;
    m_nStrings   = nStrings ;
    m_nFretDst   = nFretsDst ;
    m_nStringDst = nStringDst ;

    Init() ;
}

//----------------------------------------------------------
void
QGuitarKeyboard::Init( void)
{
    int nPos = 0 ;
    int nInc = 50 ;

    for ( int n = 0 ;  n <= m_nFrets ;  n ++) {
        m_anFrets.append( nPos);
        nPos += nInc ;
        nInc -= 3 ;
    }

    nInc = 10 ;
    for ( int n = 0 ;  n < m_nStrings ;  n ++) {
        m_anStrings.append( n * nInc);
    }
}

//----------------------------------------------------------
bool
QGuitarKeyboard::Draw( QGraphicsScene* pScene)
{
    double dHalf ;
    QSize  size ;
    QPoint ptLow ;
    QPoint ptHalf ;
    QPoint ptHigh ;
    QBrush cBrush ;

    if ( pScene == NULL) {
        return false ;
    }

    cBrush.setStyle( Qt::BrushStyle::SolidPattern);
    dHalf = m_nStringDst * 0.5 ;
    size.setWidth( m_nStringDst) ;
    size.setHeight( m_nStringDst) ;
    ptLow.setY( m_anStrings.last() * 0.33 - dHalf) ;
    ptHalf.setY( m_anStrings.last() * 0.5 - dHalf) ;
    ptHigh.setY(m_anStrings.last() * 0.66 - dHalf) ;

    foreach (int n, m_anFrets) {
        pScene->addLine(n, m_anStrings.first(), n, m_anStrings.last());
    }

    foreach (int n, m_anStrings) {
        pScene->addLine(m_anFrets.first(), n, m_anFrets.last(), n) ;
    }

    for ( int n = 0 ;  n < m_nFrets ;  n ++) {
        if ( n % 11 == 0  ||  ( n % 12 == 1  &&  n != 1)) {
            continue ;
        }

        if( n % 12 == 0) {
            ptHigh.setX(( m_anFrets[n] + m_anFrets[n-1]) * 0.5 - dHalf) ;
            ptLow.setX( ptHigh.x());
            pScene->addEllipse( QRect(ptHigh, size), QPen(), cBrush) ;
            pScene->addEllipse( QRect(ptLow, size), QPen(), cBrush) ;
        }
        else if ( n % 2 != 0  ||  n == 1) {
            ptHalf.setX(( m_anFrets[n] + m_anFrets[n-1]) * 0.5 - dHalf) ;
            pScene->addEllipse( QRect(ptHalf, size), QPen(), cBrush) ;
        }
    }

    return true ;
}
