#include "mainwindow.h"
#include <QApplication>

int maintg(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
