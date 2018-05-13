#include "lazytabsdlg.h"
#include <QApplication>

//----------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationDisplayName("Lazy Tabs");
    a.setApplicationVersion( "1.0");

    LazyTabsDlg w;
    w.show();

    return a.exec();
}
