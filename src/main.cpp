#include "mainwindow.h"
#include <QApplication>
#include "lib/OpenGL.h"


/**
  * Hauptmethode: initialisiert GLUT, initialisiert
  *  die Qt-Applikation und zeigt das Hauptfenster des GUI.
  *
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    // GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitContextVersion(4, 2);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    //glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
