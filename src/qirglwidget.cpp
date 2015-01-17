#include "qirglwidget.h"

// OpenGL helper includes
#include "lib/OpenGL.h"
#include <QGLWidget>



// system includes
#include <stdio.h>
#include <stdlib.h>
// #include <iostream>
// #include <fstream>
using namespace std;


// GLM
// #define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // initializeGL
#include <glm/gtc/type_ptr.hpp> // initializeGL
#include <glm/gtc/constants.hpp> // initializeGL
using namespace glm;

// application helper includes
// #include "lib/UtilGLUT.hpp"
// #include "lib/UtilGLSL.hpp"
// #include "lib/zpr.h"


// Qt includes
#include <QMouseEvent>

// GLM
// #define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // initializeGL
#include <glm/gtc/type_ptr.hpp> // initializeGL
#include <glm/gtc/constants.hpp> // initializeGL
using namespace glm;

/**
 * {@inheritDoc}
 */
QirGLWidget::QirGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

    /// /////////////////////////////
    /// nice grids
    /// /////////////////////////////
    glPolygonOffset(1, 1);
    glEnable(GL_POLYGON_OFFSET_FILL);

    /// /////////////////////////////
    /// keyboard and mouse
    /// /////////////////////////////
    // register callbacks
    // glutKeyboardFunc(keyboard);
    // glutSpecialFunc(specialkey);
    // glutMenuStatusFunc(updateMenu);
    // init applications
    // zprInit();
    // initMenu();

    /// /////////////////////////////
    /// camera
    /// /////////////////////////////
    // initCamera(3);

    // UtilGLSL::checkOpenGLErrorCode();

}

/**
 * {@inheritDoc}
 */
QirGLWidget::~QirGLWidget()
{
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH00(double arg){
    this->matCollineation[0][0] = arg;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH01(double arg){
    this->matCollineation[0][1] = arg;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH02(double arg){
    this->matCollineation[0][2] = arg;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH10(double arg){
    this->matCollineation[1][0] = arg;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH11(double arg){
    this->matCollineation[1][1] = arg;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH12(double arg){
    this->matCollineation[1][2] = arg;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH20(double arg){
    this->matCollineation[2][0] = arg;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH21(double arg){
    this->matCollineation[2][1] = arg;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH22(double arg){
    this->matCollineation[2][2] = arg;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH30(double arg){
    this->matCollineation[3][0] = arg;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH31(double arg){
    this->matCollineation[3][1] = arg;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH32(double arg){
    this->matCollineation[3][2] = arg;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH33(double arg){
    this->matCollineation[3][3] = arg;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::zoomIn(){
    glScalef(1.02, 1.02, 1.02);
    glutPostRedisplay();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::zoomOut(){
    glScalef(0.98, 0.98, 0.98);
    glutPostRedisplay();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::up(){
    glRotatef(-1.0, 1.0, 0.0, 0.0);
    glutPostRedisplay();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::down(){
    glRotatef(1.0, 1.0, 0.0, 0.0);
    glutPostRedisplay();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::left(){
    glRotatef(-1.0, 0.0, 1.0, 0.0);
    glutPostRedisplay();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::right(){
    glRotatef(1.0, 0.0, 1.0, 0.0);
    glutPostRedisplay();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::initializeGL()
{

}

/**
 * {@inheritDoc}
 */
void QirGLWidget::paintGL()
{

}

/**
 * {@inheritDoc}
 */
void QirGLWidget::resizeGL(int width, int height)
{


}

/**
 * {@inheritDoc}
 */
void QirGLWidget::drawAxis(GLfloat scale) {

}


void QirGLWidget::initGeometry(void) {

}


/**
 * {@inheritDoc}
 */
void QirGLWidget::drawGeometry(int type) {

}
