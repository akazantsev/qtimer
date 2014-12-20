#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("qTimer");
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("Andrey Kazantsev");
    QApplication::setOrganizationDomain("akazantsev.pp.ua");

    MainWindow w;
    w.show();

    return a.exec();
}