#include "myglwidget.h"

// System includes
#include <iostream>
#include <cmath>
using namespace std;

#include "lib/OpenGL.h"
#include "lib/zpr.h"
#include <QGLWidget>
#include <QMouseEvent>

/**
 * @brief MyGLWidget::MyGLWidget
 * @param parent
 */
MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    this->homographyMat4 = {};
    this->coefficientsMat4 = {};
    // TODO zprInit();
}


/**
 * @brief MyGLWidget::~MyGLWidget
 */
MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::setH00(double arg){
    this->homographyMat4[0][0] = arg;
}

void MyGLWidget::setH01(double arg){
    this->homographyMat4[0][1] = arg;
}
void MyGLWidget::setH02(double arg){
    this->homographyMat4[0][2] = arg;
}

void MyGLWidget::setH10(double arg){
    this->homographyMat4[1][0] = arg;
}
void MyGLWidget::setH11(double arg){
    this->homographyMat4[1][1] = arg;
}
void MyGLWidget::setH12(double arg){
    this->homographyMat4[1][2] = arg;
}

void MyGLWidget::setH20(double arg){
    this->homographyMat4[2][0] = arg;
}
void MyGLWidget::setH21(double arg){
    this->homographyMat4[2][1] = arg;
}
void MyGLWidget::setH22(double arg){
    this->homographyMat4[2][2] = arg;
}

void MyGLWidget::setH30(double arg){
    this->homographyMat4[3][0] = arg;
}
void MyGLWidget::setH31(double arg){
    this->homographyMat4[3][1] = arg;
}
void MyGLWidget::setH32(double arg){
    this->homographyMat4[3][2] = arg;
}
void MyGLWidget::setH33(double arg){
    this->homographyMat4[3][3] = arg;
}

/**
 * @brief MyGLWidget::initializeGL
 */
void MyGLWidget::initializeGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set background color
    // glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    qglClearColor(Qt::white);

    // general init
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

    // setup light parameters
    GLfloat lightPosition[] = {30.0, 10.0, 1.5, 1.0};
    GLfloat matSpecular[] = {0.8f, 0.8f, 0.8f, 1.0};
    GLfloat matShininess[] = {5.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    // force surface normal re-normalization due to scale transformation
    glEnable(GL_NORMALIZE);

    // use material color settings
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

}


/**
 * @brief MyGLWidget::paintGL
 */
void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(32.0, 1.0, 0.0, 0.0);
    glRotatef(32.0, 0.0, 1.0, 0.0);
    glRotatef(32.0, 0.0, 0.0, 1.0);
    draw();
}


/**
 * @brief MyGLWidget::resizeGL
 * @param width
 * @param height
 */
void MyGLWidget::resizeGL(int width, int height)
{

}

/**
 * @brief MyGLWidget::draw
 */
void MyGLWidget::draw(void)
{
    qglColor(Qt::cyan);
    glutWireSphere(1.0,10,10);
}
