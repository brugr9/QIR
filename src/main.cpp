#include "mainwindow.h"
#include <QApplication>
#include "lib/OpenGL.h"

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
