#include "mainwindow.h"
#include <QApplication>
int GameWindow::n=1;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
