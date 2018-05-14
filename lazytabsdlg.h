#pragma once

#include <QDialog>
#include <QClipboard>
#include "tabsscene.h"

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

    private slots:
        void on_addChord_clicked();
        void on_sendToClip_clicked();
        void on_config_clicked();

private:
        Ui::LazyTabsDlg *ui;
        TabsScene*       m_pScene ;
};

