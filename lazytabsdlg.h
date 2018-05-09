#pragma once

#include <QDialog>
#include <QGraphicsScene>
#include "qguitarkeyboard.h"

namespace Ui {
class LazyTabsDlg;
}

class LazyTabsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LazyTabsDlg(QWidget *parent = 0);
    ~LazyTabsDlg();

protected:
    bool DrawKeyboard( void) ;

private:
    Ui::LazyTabsDlg *ui;
    QGraphicsScene*  m_pScene ;
    QGuitarKeyboard  m_cKey ;
};

