#pragma once

#include <QSettings>

//----------------------------------------------------------
class config
{
    public:
        config();
        QString GetLang( void) ;
        void GetValues( int* pnStrings, int* pnFrets) ;
        void SetValues( int nStrings, int nFrets, const QString& szLang, const QString& szDBFile) ;
        QString GetDbFile( void) ;
        QStringList GetLangList( void) ;

    private:
        QString   m_szLangKey ;
        QString   m_szFretsKey ;
        QString   m_szDbFileKey ;
        QString   m_szStringsKey ;
        QSettings m_set ;
};
