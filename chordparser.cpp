#include "chordparser.h"
#include <QFile>
#include <QTextStream>

//----------------------------------------------------------
chordParser::chordParser( void)
{
}

//----------------------------------------------------------
bool
chordParser::initMaps( const QString& szDb)
{
    if ( szDb.isEmpty()) {
        return false ;
    }

    QFile file( szDb) ;
    if ( ! file.open( QIODevice::ReadOnly | QIODevice::Text)) {
        return false ;
    }

    m_mGuitar.clear() ;
    m_mUkulele.clear() ;

    QStringList slTokens ;
    QTextStream stream( &file) ;

    while( ! stream.atEnd()) {
        slTokens = stream.readLine().split( ";") ;
        if ( slTokens.size() < 2) {
            continue ;
        }
        QStringList slValues = slTokens[1].split( " ") ;
        for ( int i = 0 ;  i < slValues.size() ;  i ++) {
            m_mGuitar[slTokens[0]].append( slValues[i].toInt()) ;
        }

        if ( slTokens.size() == 3) {
            slValues.clear() ;
            slValues = slTokens[2].split( " ") ;
            for ( int i = 0 ;  i < slValues.size() ;  i ++) {
                m_mUkulele[slTokens[0]].append( slValues[i].toInt()) ;
            }
        }
    }

    file.close() ;

    return true ;
}

//----------------------------------------------------------
bool
chordParser::parse( const QString& szRaw, QVector<int>* pRes)
{
    QString szRes ;
    QString szInput ;

    if ( szRaw.isEmpty()  ||  pRes == nullptr) {
        return false ;
    }

    QStringList slValues = szRaw.split( " ") ;
    for ( int n = 0 ;  n < slValues.size() ;  n ++) {
        if ( ! slValues[n].isEmpty()) {
            pRes->append( slValues[n].toInt()) ;
        }
    }

    return true ;
}

//----------------------------------------------------------
bool
chordParser::parse( const QString& szRaw, chordsMode nMode, QVector<int>* pRes)
{
    QString szRes ;
    QString szInput ;

    if ( szRaw.isEmpty()  ||  pRes == nullptr) {
        return false ;
    }

    pRes->clear() ;
    szInput = szRaw.toLower().replace( " ", "") ;

    if ( szInput.size() > 3) {
        return false ;
    }

    if ( nMode == GUITAR) {
        pRes->append( m_mGuitar[szInput]) ;
    }
    else if ( nMode == UKULELE) {
        pRes->append( m_mUkulele[szInput]) ;
    }

    return true ;
}

//----------------------------------------------------------
bool
chordParser::parseFile( const QString& szFile, QStringList* pRes)
{
    if ( pRes == nullptr) {
        return false ;
    }

    QFile file( szFile) ;
    if ( ! file.open( QIODevice::ReadOnly | QIODevice::Text)) {
        return false ;
    }

    QString szLine ;
    QTextStream stream( &file) ;
    while ( ! stream.atEnd()) {
        szLine = stream.readLine() ;
        if ( ! szLine.isEmpty()) {
            pRes->append( szLine) ;
        }
    }

    file.close() ;

    return true ;
}
