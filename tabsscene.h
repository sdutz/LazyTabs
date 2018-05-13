#pragma once

#include <QGraphicsScene>
#include "qguitarkeyboard.h"

//----------------------------------------------------------
class TabsScene : public QGraphicsScene
{
    public:
        TabsScene( QObject* pParent = NULL);

    protected:
        void mousePressEvent( QGraphicsSceneMouseEvent* pEvent);

    private:
        QGuitarKeyboard  m_cKey ;
};
