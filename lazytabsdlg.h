#pragma once

#include <QDialog>
#include "tabsscene.h"

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

    private:
        Ui::LazyTabsDlg *ui;
        TabsScene*       m_pScene ;
};

