#include "mainwindow.h"
#include "form.h"
//#include "screen_1.h"
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	a.setWindowIcon(QIcon(":/Images/JAHIcon.png"));
    a.setApplicationName( QString("JAH Lights Console GUI") );
    MainWindow w;
    w.setWindowTitle(QString("JAH Lights Console GUI"));
    w.show();
//        screen_1 s1;
//        s1.show();
    return a.exec();
}
