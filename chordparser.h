#pragma once

#include<QString>
#include<QMap>

enum chordsMode {
    GUITAR,
    UKULELE
} ;

//----------------------------------------------------------
class chordParser
{
    public :
        chordParser( void) ;
        QString parse( const QString& szRaw, chordsMode nMode) ;

    protected :
        void InitMaps( void) ;

    private :
        QMap<QString,QString> m_mGuitar ;
        QMap<QString,QString> m_mUkulele ;
} ;
