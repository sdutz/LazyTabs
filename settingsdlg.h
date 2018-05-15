#pragma once

#include <QDialog>
#include "config.h"

//----------------------------------------------------------
namespace Ui {
    class settingsdlg;
}

//----------------------------------------------------------
class settingsdlg : public QDialog
{
    Q_OBJECT

    public:
        explicit settingsdlg(QWidget *parent = 0);
        ~settingsdlg();

    private slots:
        void on_settingsdlg_accepted();

    private:
        config          m_conf ;
        Ui::settingsdlg *ui;
};
