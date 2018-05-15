#pragma once

#include <QSettings>

//----------------------------------------------------------
class config
{
    public:
        config();
        void GetValues( int* pnStrings, int* pnFrets) ;
        void SetValues( int nStrings, int nFrets) ;

    private:
        QString   m_szFretsKey ;
        QString   m_szStringsKey ;
        QSettings m_set ;
};
