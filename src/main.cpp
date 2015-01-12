#include "mainwindow.h"
#include <QApplication>
#include "lib/OpenGL.h"

/**
  * Hauptmethode: initialisiert GLUT und die Qt-Applikation, zeigt das Hauptfenster des GUI.
  *
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
