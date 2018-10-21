#pragma once

#include <QDialog>
#include <QTranslator>
#include "tabsscene.h"
#include "config.h"

//----------------------------------------------------------
namespace Ui {
    class LazyTabsDlg;
}

//----------------------------------------------------------
class LazyTabsDlg : public QDialog
{
    Q_OBJECT

    public:
        explicit LazyTabsDlg(QWidget *parent = nullptr);
        ~LazyTabsDlg();

    protected:
        bool Init( void) ;
        bool SetLang( bool bInit) ;

    private slots:
        void on_addChord_clicked();
        void on_sendToClip_clicked();
        void on_config_clicked();

        void on_leftShift_clicked();

        void on_rightShift_clicked();

        void on_reset_clicked();

        void on_insertChord_clicked();

private:
        Ui::LazyTabsDlg *ui;
        config           m_conf ;
        TabsScene*       m_pScene ;
        QTranslator      m_cLang ;
};

