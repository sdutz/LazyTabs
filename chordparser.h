#pragma once

#include<QString>
#include<QVector>
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
        bool initMaps( const QString& szDb) ;
        bool parse( const QString& szRaw, QVector<int>* pRes) ;
        bool parse( const QString& szRaw, chordsMode nMode, QVector<int>* pRes) ;
        bool parseFile( const QString& szFile, QStringList* pRes) ;
    protected :

    private :
        QMap<QString,QVector<int>> m_mGuitar ;
        QMap<QString,QVector<int>> m_mUkulele ;
} ;
