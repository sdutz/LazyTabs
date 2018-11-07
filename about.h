#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

    public:
        explicit About(QWidget *parent = nullptr);
        ~About();

    protected:
        QString GetInfo( void) ;
        void FillShortCutsList( void) ;
        void mousePressEvent( QMouseEvent* pEvent) ;

    private:
        Ui::About   *ui;
        QStringList m_lszShortCuts ;
};

#endif // ABOUT_H
