#pragma once

#include <QDialog>
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
        explicit LazyTabsDlg(QWidget *parent = 0);
        ~LazyTabsDlg();

    protected:
        bool Init() ;

    private slots:
        void on_addChord_clicked();
        void on_sendToClip_clicked();
        void on_config_clicked();

        void on_leftShift_clicked();

        void on_rightShift_clicked();

        void on_reset_clicked();

private:
        Ui::LazyTabsDlg *ui;
        config           m_conf ;
        TabsScene*       m_pScene ;
};

