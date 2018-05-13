#include "tabsscene.h"


//----------------------------------------------------------
TabsScene::TabsScene( QObject* pParent /*= NULL*/) : QGraphicsScene( pParent)
{
    m_cKey.Draw( this) ;
}

//----------------------------------------------------------
void
TabsScene::mousePressEvent( QGraphicsSceneMouseEvent* pEvent)
{
    if ( pEvent == NULL){
        return ;
    }


}
