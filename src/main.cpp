// OpenGL helper includes
#include "lib/OpenGL.h"
// #include "lib/UtilGLSL.hpp"

// Qt includes
#include "mainwindow.h"
#include <QApplication>

//
#include "qirmodel.h"

/**
  * Hauptmethode: initialisiert GLUT, lädt die Shader-Programme, initialisiert
  *  die Qt-Applikation und zeigt das Hauptfenster des GUI.
  *
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    /*
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitContextVersion(4, 2);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    */

    // load shader programs
    /*
    argc = 3;
    argv[0] = "";
    argv[1] = "glsl/qir.vert";
    argv[2] = "glsl/qir.frag";
    PROGRAM_ID = UtilGLSL::initShaderProgram(argc, argv);
    */

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
