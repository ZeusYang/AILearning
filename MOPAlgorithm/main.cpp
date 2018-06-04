#include <QApplication>
#include "Display.h"
#include <QDebug>

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    Display window;
    window.show();
    return app.exec();
}
