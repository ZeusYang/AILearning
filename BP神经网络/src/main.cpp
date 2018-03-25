#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    MainWindow window;
    window.show();
    //window.Test();
    //window.aStarAlgorithm();
    return app.exec();
}
