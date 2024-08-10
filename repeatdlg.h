#ifndef REPEATDLG_H
#define REPEATDLG_H

#include <QDialog>

//----------------------------------------------------------
namespace Ui {
class RepeatDlg;
}


//----------------------------------------------------------
class RepeatDlg : public QDialog
{
    Q_OBJECT

    public:
        explicit RepeatDlg(QWidget *parent = nullptr);
        void getRes(int& nStart, int& nChords, int& nCount) ;
        ~RepeatDlg();

    private:
        Ui::RepeatDlg *ui;
};

#endif // REPEATDLG_H
