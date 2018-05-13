#include "tabsscene.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMoveEvent>

//----------------------------------------------------------
TabsScene::TabsScene( QObject* pParent /*= NULL*/) : QGraphicsScene( pParent)
{
    m_nFrets     = 14 ;
    m_nStrings   = 6 ;
    m_nFretDst   = 50 ;
    m_nStringDst = 10 ;
}

//----------------------------------------------------------
void
TabsScene::SetData( int nStrings, int nFrets, int nStringDst, int nFretsDst)
{
    m_nFrets     = nFrets ;
    m_nStrings   = nStrings ;
    m_nFretDst   = nFretsDst ;
    m_nStringDst = nStringDst ;
}

//----------------------------------------------------------
void
TabsScene::mouseDoubleClickEvent( QGraphicsSceneMouseEvent* pEvent)
{
    int nString ;

    if ( pEvent == NULL){
        return ;
    }

    if ( ! Pick( pEvent->scenePos(), &nString)  ||
         m_anVals[nString].pSymbol == NULL) {
        return ;
    }

    m_anVals[nString].nVal = m_anVals[nString].nVal == 0 ? -1 : 0 ;
    m_anVals[nString].pSymbol->setBrush( GetValBrush( m_anVals[nString].nVal == 0));
    m_anVals[nString].pSymbol->setPos( - m_nStringDst * 0.5, m_anVals[nString].pSymbol->pos().y());
}

//----------------------------------------------------------
bool
TabsScene::Pick( const QPointF& ptScene, int* pnString, int* pnFret /*= NULL*/)
{
    int nString ;

    if ( pnString == NULL) {
        return false ;
    }

    nString = ptScene.y() / m_nStringDst ;
    if ( nString > m_nStringDst) {
        return false ;
    }

    *pnString = nString ;

    if ( pnFret == NULL){
        return true ;
    }

    int nFret ;
    nFret = -1 ;
    if ( ptScene.x() < 0){
        nFret = 0 ;
    }
    else {
        for ( int n = 1 ;  n < m_nFrets  &&  nFret < 0 ;  n ++) {
            if ( ptScene.x() > m_anFrets[n-1]  &&
                 ptScene.x() <= m_anFrets[n]) {
                nFret = n ;
            }
        }
    }

    if ( nFret < 0){
        return false ;
    }

    *pnFret = nFret ;

    return true ;
}

//----------------------------------------------------------
void
TabsScene::mousePressEvent( QGraphicsSceneMouseEvent* pEvent)
{
    int    nFret ;
    int    nString ;
    double dPos ;

    if ( pEvent == NULL) {
        return ;
    }

    dPos = 0 ;

    if ( ! Pick( pEvent->scenePos(), &nString, &nFret)  ||
         m_anVals[nString].pSymbol == NULL) {
        return ;
    }

    m_anVals[nString].nVal = nFret ;
    if ( nFret > 0) {
        dPos = ( m_anFrets[nFret] + m_anFrets[nFret-1]) * 0.5 - m_nStringDst * 0.5 ;
    }

    m_anVals[nString].pSymbol->setBrush( GetValBrush( true));
    m_anVals[nString].pSymbol->setPos( dPos, m_anVals[nString].pSymbol->pos().y());
}

//----------------------------------------------------------
void
TabsScene::Init( void)
{
    int nPos = 0 ;
    int nInc = 50 ;

    m_anFrets.resize( m_nFrets);
    m_anVals.resize( m_nStrings);
    m_anStrings.resize( m_nStrings);

    for ( int n = 0 ;  n < m_nFrets ;  n ++) {
        m_anFrets[n] = nPos ;
        nPos += nInc ;
        nInc -= 3 ;
    }

    nInc = 10 ;
    for ( int n = 0 ;  n < m_nStrings ;  n ++) {
        m_anStrings[n] = n * nInc ;
    }
}

//----------------------------------------------------------
bool
TabsScene::Draw( void)
{
    double dHalf ;
    pos    cPos ;
    QPen   cPen ;
    QSize  size ;
    QPoint ptLow ;
    QPoint ptVal ;
    QPoint ptHalf ;
    QPoint ptHigh ;
    QBrush cBrush ;
    QBrush cValBrush ;

    Init();

    cBrush.setStyle( Qt::BrushStyle::SolidPattern);
    cValBrush = GetValBrush( true) ;
    dHalf = m_nStringDst * 0.5 ;
    size.setWidth( m_nStringDst) ;
    size.setHeight( m_nStringDst) ;
    ptVal.setX( - dHalf);
    ptLow.setY( m_anStrings.last() * 0.33 - dHalf) ;
    ptHalf.setY( m_anStrings.last() * 0.5 - dHalf) ;
    ptHigh.setY(m_anStrings.last() * 0.66 - dHalf) ;

    foreach (int n, m_anFrets) {
        addLine(n, m_anStrings.first(), n, m_anStrings.last());
    }

    for ( int n = 0 ;  n < m_nStrings ;  n ++) {
        addLine(m_anFrets.first(), m_anStrings[n], m_anFrets.last(), m_anStrings[n]) ;
        ptVal.setY( m_anStrings[n] - dHalf);
        cPos.pSymbol = addEllipse( QRect( ptVal, size), cPen, cValBrush) ;
        m_anVals[n]  = cPos ;
    }

    for ( int n = 0 ;  n < m_nFrets ;  n ++) {
        if ( n % 11 == 0  ||  ( n % 12 == 1  &&  n != 1)) {
            continue ;
        }

        if( n % 12 == 0) {
            ptHigh.setX(( m_anFrets[n] + m_anFrets[n-1]) * 0.5 - dHalf) ;
            ptLow.setX( ptHigh.x());
            addEllipse( QRect(ptHigh, size), cPen, cBrush) ;
            addEllipse( QRect(ptLow, size), cPen, cBrush) ;
        }
        else if ( n % 2 != 0  ||  n == 1) {
            ptHalf.setX(( m_anFrets[n] + m_anFrets[n-1]) * 0.5 - dHalf) ;
            addEllipse( QRect(ptHalf, size), cPen, cBrush) ;
        }
    }

    return true ;
}

//----------------------------------------------------------
QBrush
TabsScene::GetValBrush( bool bActive)
{
    QBrush cBrush ;

    cBrush.setStyle( Qt::BrushStyle::SolidPattern) ;
    cBrush.setColor( bActive ? Qt::green : Qt::gray) ;

    return cBrush ;
}
