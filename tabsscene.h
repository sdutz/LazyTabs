#pragma once

#include <QGraphicsScene>

//----------------------------------------------------------
struct pos {
    int                    nVal ;
    QGraphicsEllipseItem * pSymbol ;

    pos() {
        nVal    = 0 ;
        pSymbol = NULL ;
    }
} ;

//----------------------------------------------------------
class TabsScene : public QGraphicsScene
{
    public:
        TabsScene( QObject* pParent = NULL);
        void SetData( int nStrings, int nFrets);
        bool Draw( void) ;
        QString GetChord( void) ;

    protected:
        void Init( void) ;
        bool Pick( const QPointF& ptScene, int* pnString, int* pnFret = NULL) ;
        void mousePressEvent( QGraphicsSceneMouseEvent* pEvent);
        void mouseDoubleClickEvent( QGraphicsSceneMouseEvent* pEvent);
        QBrush GetValBrush( bool bActive) ;
        void GetSizes( QVector<qreal>* pafSizes) ;

    private:
        int          m_nFrets ;
        int          m_nStrings ;
        int          m_nFretDst ;
        int          m_nStringDst ;
        QVector<int> m_anFrets ;
        QVector<int> m_anStrings ;
        QVector<pos> m_anVals ;
};
