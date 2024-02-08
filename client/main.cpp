#include <QApplication>
#include "mainwindow.h"
#include "program.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Program mainProg;
    MainWindow w(nullptr, &mainProg);
    w.show();
    return a.exec();
}
