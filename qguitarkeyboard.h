#pragma once

#include <QGraphicsScene>

class QGuitarKeyboard {
    public:
        explicit QGuitarKeyboard();
        explicit QGuitarKeyboard( int nStrings, int nFrets, int nStringDst, int nFretsDst);
        bool Draw( QGraphicsScene* pScene) ;

    protected:
        void Init( void) ;

    private:
        int          m_nFrets ;
        int          m_nStrings ;
        int          m_nFretDst ;
        int          m_nStringDst ;
        QVector<int> m_anFrets ;
        QVector<int> m_anStrings ;
};
