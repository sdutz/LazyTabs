#include "tabsscene.h"
#include <math.h>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMoveEvent>
#include <QMessageBox>

//----------------------------------------------------------
TabsScene::TabsScene( QObject* pParent /*= NULL*/) : QGraphicsScene( pParent)
{
    m_nFrets     = 14 ;
    m_nStrings   = 6 ;
    m_nFretDst   = 60 ;
    m_nStringDst = 10 ;
}

//----------------------------------------------------------
void
TabsScene::SetData( int nStrings, int nFrets)
{
    m_nFrets   = nFrets ;
    m_nStrings = nStrings ;
}

//----------------------------------------------------------
void
TabsScene::mouseDoubleClickEvent( QGraphicsSceneMouseEvent* pEvent)
{
    int nString ;

    if ( pEvent == nullptr){
        return ;
    }

    if ( ! Pick( pEvent->scenePos(), &nString)  ||
         m_anVals[nString].pSymbol == nullptr) {
        return ;
    }

    m_anVals[nString].nVal = m_anVals[nString].nVal >= 0 ? -1 : 0 ;
    m_anVals[nString].pSymbol->setBrush( GetValBrush( m_anVals[nString].nVal == 0));
    m_anVals[nString].pSymbol->setPos( - m_nStringDst * 0.5, m_anVals[nString].pSymbol->pos().y());
}

//----------------------------------------------------------
bool
TabsScene::Pick( const QPointF& ptScene, int* pnString, int* pnFret /*= NULL*/)
{
    int    nString ;
    double dPos ;

    if ( pnString == nullptr) {
        return false ;
    }

    dPos = ptScene.y() / m_nStringDst ;
    if ( dPos < - m_nStringDst) {
        return false ;
    }
    else if ( dPos < 0) {
        nString = 0 ;
    }
    else {
        nString = static_cast<int>( ( dPos - floor( dPos) > 0.5) ? ceil( dPos) : floor( dPos)) ;
    }

    if ( nString >= m_nStrings) {
        return false ;
    }

    *pnString = nString ;

    if ( pnFret == nullptr){
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
    int nFret ;
    int nString ;

    if ( pEvent == nullptr) {
        return ;
    }

    if ( ! Pick( pEvent->scenePos(), &nString, &nFret)  ||
         m_anVals[nString].pSymbol == nullptr) {
        return ;
    }

    m_anVals[nString].nVal = nFret ;

    DrawPos( nString) ;
}

//----------------------------------------------------------
void
TabsScene::DrawPos( int nString)
{
    int    nFret ;
    double dPos = 0. ;

    nFret = m_anVals[nString].nVal ;

    if ( nFret > 0) {
        dPos = ( m_anFrets[nFret] + m_anFrets[nFret-1]) * 0.5 ;
        m_anVals[nString].pSymbol->setBrush( GetValBrush( true));
        m_anVals[nString].pSymbol->setPos( dPos, m_anVals[nString].pSymbol->pos().y());
    }
    else if ( nFret == 0) {
        m_anVals[nString].pSymbol->setBrush( GetValBrush( true));
        m_anVals[nString].pSymbol->setPos( 0., m_anVals[nString].pSymbol->pos().y());
    }
    else {
        m_anVals[nString].pSymbol->setBrush( GetValBrush( false));
        m_anVals[nString].pSymbol->setPos( - m_nStringDst * 0.5, m_anVals[nString].pSymbol->pos().y());
    }
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

    clear();
}

//----------------------------------------------------------
bool
TabsScene::Draw( void)
{
    double dHalf ;
    pos    cPos ;
    QPen   cPen ;
    QPen   cSPen ;
    QSize  size ;
    QPoint ptLow ;
    QPoint ptVal ;
    QPoint ptHalf ;
    QPoint ptHigh ;
    QBrush cBrush ;
    QBrush cValBrush ;
    QVector<qreal> afSizes ;

    Init();

    cBrush.setStyle( Qt::BrushStyle::SolidPattern);
    cValBrush = GetValBrush( true) ;
    dHalf = m_nStringDst * 0.5 ;
    size.setWidth( m_nStringDst) ;
    size.setHeight( m_nStringDst) ;
    ptVal.setX( static_cast<int>( - dHalf)) ;
    ptLow.setY( static_cast<int>( m_anStrings.last() * 0.33 - dHalf)) ;
    ptHalf.setY( static_cast<int>( m_anStrings.last() * 0.5 - dHalf)) ;
    ptHigh.setY( static_cast<int>( m_anStrings.last() * 0.66 - dHalf)) ;

    foreach (int n, m_anFrets) {
        addLine( n, m_anStrings.first(), n, m_anStrings.last());
    }

    GetSizes(&afSizes);

    for ( int n = 0 ;  n < m_nStrings ;  n ++) {
        cSPen.setWidthF(afSizes[n]);
        addLine(m_anFrets.first(), m_anStrings[n], m_anFrets.last(), m_anStrings[n], cSPen) ;
        ptVal.setY( static_cast<int>( m_anStrings[n] - dHalf)) ;
        cPos.pSymbol = addEllipse( QRect( ptVal, size), cPen, cValBrush) ;
        cPos.pSymbol->setZValue( 1);
        m_anVals[n]  = cPos ;
    }

    for ( int n = 0 ;  n < m_nFrets ;  n ++) {
        if ( n % 11 == 0  ||  ( n % 12 == 1  &&  n != 1)) {
            continue ;
        }

        if( n % 12 == 0) {
            ptHigh.setX( static_cast<int>( ( m_anFrets[n] + m_anFrets[n - 1]) * 0.5 - dHalf)) ;
            ptLow.setX( ptHigh.x());
            addEllipse( QRect( ptHigh, size), cPen, cBrush) ;
            addEllipse( QRect( ptLow, size), cPen, cBrush) ;
        }
        else if ( n % 2 != 0  ||  n == 1) {
            ptHalf.setX( static_cast<int>( ( m_anFrets[n] + m_anFrets[n - 1]) * 0.5 - dHalf)) ;
            addEllipse( QRect( ptHalf, size), cPen, cBrush) ;
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

//----------------------------------------------------------
QString
TabsScene::GetChord( void)
{
    QString szChord ;

    if ( ! isCurrValid()) {
        return szChord ;
    }

    foreach ( pos cPos, m_anVals) {
        szChord += cPos.nVal < 0 ? "X " : QString::number( cPos.nVal) + " ";
    }

    return szChord ;
}

//----------------------------------------------------------
void
TabsScene::GetSizes( QVector<qreal>* pafSizes)
{
    if ( pafSizes == nullptr) {
        return ;
    }

    pafSizes->resize( m_nStrings);

    switch ( m_nStrings) {
        case 6:
            (*pafSizes) = { 3., 2.5, 2., 1.5, 1., 0.5, 0.1} ;
            break;
        case 4:
            (*pafSizes) = { 0.5, 2., 1., 0.1} ;
            break ;
        default:
            pafSizes->fill( 1) ;
            break;
    }
}

//----------------------------------------------------------
void
TabsScene:: Move( bool bLeft)
{
    for ( int i = 0 ;  i < m_anVals.count() ;  i ++) {
        if ( bLeft  &&  m_anVals[i].nVal > 0) {
            m_anVals[i].nVal -- ;
            DrawPos( i) ;
        }
        else if ( ! bLeft  &&  m_anVals[i].nVal < m_nFrets - 1  &&  m_anVals[i].nVal >= 0) {
            m_anVals[i].nVal ++ ;
            DrawPos( i) ;
        }
    }
}

//----------------------------------------------------------
void
TabsScene:: Reset( void)
{
    for ( int i = 0 ;  i < m_anVals.count() ;  i ++) {
        m_anVals[i].nVal = 0 ;
        DrawPos(i) ;
    }
}

//----------------------------------------------------------
bool
TabsScene::isCurrValid( void)
{
    int nMin ;
    int nMax ;
    int nMaxDiff ;

    nMax = 0 ;
    nMin = m_nFrets ;
    nMaxDiff = m_nStrings == 4 ? 6 : 4 ;

    foreach ( pos p, m_anVals) {
        if ( p.nVal > 0) {
            nMin = qMin( nMin, p.nVal) ;
            nMax = qMax( nMax, p.nVal) ;
        }
    }

    if ( ( nMax - nMin) <= nMaxDiff) {
        return true ;
    }

    return QMessageBox::warning( static_cast<QWidget*> (parent()), tr("Warning"),
                                 tr("this cord will stretch your hand, are you sure it's correct?"),
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes ;
}


//----------------------------------------------------------
bool
TabsScene::SetChord( const QVector<int>& anVals)
{
    if ( m_anVals.size() != anVals.size()) {
        return false ;
    }

    for ( int n = 0 ;  n < m_anVals.size() ;  n ++) {
        m_anVals[n].nVal = anVals[n] ;
        DrawPos( n) ;
    }

    return true ;
}
