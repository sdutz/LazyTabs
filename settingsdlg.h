#ifndef SETTINGSDLG_H
#define SETTINGSDLG_H

#include <QDialog>

namespace Ui {
class settingsdlg;
}

class settingsdlg : public QDialog
{
    Q_OBJECT

public:
    explicit settingsdlg(QWidget *parent = 0);
    ~settingsdlg();

private:
    Ui::settingsdlg *ui;
};

#endif // SETTINGSDLG_H
