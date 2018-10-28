#pragma once

#include <QDialog>
#include <QTranslator>
#include "tabsscene.h"
#include "config.h"
#include "chordparser.h"

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
        bool Init( bool bFromFile = false) ;
        bool SetLang( bool bInit) ;
        void keyPressEvent( QKeyEvent* pEvent) ;

    private slots:
        void on_addChord_clicked();
        void on_sendToClip_clicked();
        void on_config_clicked();
        void on_leftShift_clicked();
        void on_rightShift_clicked();
        void on_reset_clicked();
        void on_insertChord_clicked();
        void on_exit_clicked();
        void on_load_clicked();
        void on_save_clicked();
        void closeEvent( QCloseEvent* pEvent) ;

private:
        Ui::LazyTabsDlg *ui;
        bool             m_bMod ;
        config           m_conf ;
        chordParser      m_parser ;
        TabsScene*       m_pScene ;
        QTranslator      m_cLang ;
};

