#pragma once

#include <QGraphicsScene>

class QGuitarKeyboard {
    public:
        explicit QGuitarKeyboard();
        bool Draw( QGraphicsScene* pScene) ;

    protected:
        void Init() ;

    private:
        QVector<int> m_anFrets ;
        QVector<int> m_anStrings ;
};
