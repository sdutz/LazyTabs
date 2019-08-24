#pragma once

#include <QGraphicsScene>

//----------------------------------------------------------
struct pos {
    int                    nVal ;
    QGraphicsEllipseItem * pSymbol ;

    pos() {
        nVal    = 0 ;
        pSymbol = nullptr ;
    }
} ;

//----------------------------------------------------------
class TabsScene : public QGraphicsScene
{
    public:
        TabsScene( bool bDark, QObject* pParent = nullptr);
        void SetData( int nStrings, int nFrets);
        bool Draw( void) ;
        QString GetChord( void) ;
        void Move( bool bLeft) ;
        void Reset( void) ;
        bool SetChord( const QVector<int>& anVals) ;

    protected:
        void Init( void) ;
        bool Pick( const QPointF& ptScene, int* pnString, int* pnFret = nullptr) ;
        void mousePressEvent( QGraphicsSceneMouseEvent* pEvent);
        void mouseDoubleClickEvent( QGraphicsSceneMouseEvent* pEvent);
        QBrush GetValBrush( bool bActive) ;
        void GetSizes( QVector<qreal>* pafSizes) ;
        void DrawPos( int nString) ;
        bool isCurrValid( void) ;

    private:
        int          m_nFrets ;
        int          m_nStrings ;
        int          m_nFretDst ;
        int          m_nStringDst ;
        QColor       m_col ;
        QVector<int> m_anFrets ;
        QVector<int> m_anStrings ;
        QVector<pos> m_anVals ;
};
