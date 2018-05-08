#include "lazytabsdlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LazyTabsDlg w;
    w.show();

    return a.exec();
}
