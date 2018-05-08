#ifndef LAZYTABSDLG_H
#define LAZYTABSDLG_H

#include <QDialog>

namespace Ui {
class LazyTabsDlg;
}

class LazyTabsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LazyTabsDlg(QWidget *parent = 0);
    ~LazyTabsDlg();

private:
    Ui::LazyTabsDlg *ui;
};

#endif // LAZYTABSDLG_H
