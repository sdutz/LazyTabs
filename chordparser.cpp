#include "chordparser.h"

//----------------------------------------------------------
chordParser::chordParser( void)
{
    InitMaps() ;
}

//----------------------------------------------------------
void
chordParser::InitMaps( void)
{
    m_mGuitar["e+"] = "022100" ;
}

//----------------------------------------------------------
QString
chordParser::parse( const QString& szRaw, chordsMode nMode)
{
    QString szRes ;
    QString szInput ;

    if ( szRaw.isEmpty()) {
        return szRes ;
    }

    szInput = szRaw.toLower().replace( " ", "") ;

    if ( szInput.size() > 3) {
        return szRes ;
    }

    if ( nMode == GUITAR) {
        szRes = m_mGuitar[szInput] ;
    }
    else if ( nMode == UKULELE) {
        szRes = m_mUkulele[szInput] ;
    }

    return szRes ;
}

