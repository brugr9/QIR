#include "qirglwidget.h"

// system includes
#include <stdio.h>
#include <stdlib.h>
// #include <iostream>
// #include <fstream>
using namespace std;

// Qt includes
#include <QMouseEvent>

// OpenGL helper includes
#include "lib/OpenGL.h"
#include <QGLWidget>

// GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // initializeGL
#include <glm/gtc/type_ptr.hpp> // initializeGL
#include <glm/gtc/constants.hpp> // initializeGL
using namespace glm;


// R-G-B-A
const GLfloat RED[] = { 1.0, 0.0, 0.0, 1.0 };
const GLfloat GREEN[] = { 0.0, 1.0, 0.0, 1.0 };
const GLfloat BLUE[] = { 0.0, 0.0, 1.0, 1.0 };
const GLfloat WHITE[] = { 1.0, 1.0, 1.0, 1.0 };
// C-M-Y-A
const GLfloat CYAN[] = { 0.0, 1.0, 1.0, 1.0 };
const GLfloat MAGENTA[] = { 1.0, 0.0, 1.0, 1.0 };
const GLfloat YELLOW[] = { 1.0, 1.0, 0.0, 1.0 };
const GLfloat BLACK[] = { 0.0, 0.0, 0.0, 1.0 };
//
const GLfloat GREY[] = { 0.41, 0.49, 0.57, 1.0 };


// Quadrik (qobj)
int qType = 0;

GLuint startList;
const GLuint NUMBER_OF_FIGURES = 4;
const GLuint NUMBER_OF_ENTRIES_PER_FIGURE = 3;
bool BOUNDING_BOX = false;



/**
 * {@inheritDoc}
 */
QirGLWidget::QirGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    this->projectionType = ORTHOGRAPHIC;
    this->WIREFRAME_MODE = false;
    this->ORIENTATION_DRAW = true;
    this->zoomOutValue = 0.98;
    this->zoomInValue = 2 - this->zoomOutValue;
    this->rotateValue = 1.2;
    // initCamera(this->camera, 2);
    this->errorCallback = 0;
    this->initializeGL();
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
void QirGLWidget::initializeGL()
{
    // nice grids
    glPolygonOffset(1, 1);
    glEnable(GL_POLYGON_OFFSET_FILL);

    // background color
    //glClearColor(BLACK[0], BLACK[1], BLACK[2], BLACK[3]); // white
    glClearColor(WHITE[0], WHITE[1], WHITE[2], WHITE[3]); // black

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GLU_POINT);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    //* define material properties
    GLfloat MAT_AMBIENT[4];
    GLfloat MAT_DIFFUSE[4];
    GLfloat MAT_SPECULAR[4];
    GLfloat MAT_SHININESS[4];
    GLfloat MAT_EMISSION[4];

    //*
    MAT_AMBIENT[0] = 0.2125F;
    MAT_AMBIENT[1] = 0.1275F;
    MAT_AMBIENT[2] = 0.0540F;
    MAT_AMBIENT[3] = 1.0000F;

    MAT_DIFFUSE[0] = 0.7140F;
    MAT_DIFFUSE[1] = 0.4284F;
    MAT_DIFFUSE[2] = 0.1814F;
    MAT_DIFFUSE[3] = 1.0000F;

    MAT_SPECULAR[0] = 0.3935F;
    MAT_SPECULAR[1] = 0.2719F;
    MAT_SPECULAR[2] = 0.1667F;
    MAT_SPECULAR[3] = 1.0000F;

    MAT_SHININESS[0] = 25.6F;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MAT_AMBIENT);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MAT_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MAT_SPECULAR);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MAT_SHININESS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, MAT_EMISSION);

    // define stationary light source properties
    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat pos[] = { 1.0, 1.0, 1.0, 0.0 };

    // GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    // GL_LIGHT1
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_POSITION, pos);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);

    this->initGeometry();

}

/**
 * {@inheritDoc}
 */
void QirGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Orthografische Projektion

        //initialize viewing values
        glMatrixMode(GL_MODELVIEW);

        // draw
        glPushMatrix();
        // if (this->AXIS_DRAW) {
            this->drawOrientation(1.2);
        //}
        drawGeometry(0);
        glPopMatrix();


    if (this->STEREOSCOPE_DRAW) {
        // Stereografische Projektion
        // stereoscope();
    }
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::resizeGL(int width, int height)
{

    // camera.swidth = width;
    // camera.sheight = height;

    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20, (GLdouble) width / height, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // define fixed light source positions
    GLfloat position0[] = { 0.0, 5.0, 0.0, 0.0 };
    GLfloat position1[] = { 5.0, 0.7, 0.0, 0.0 };
    GLfloat position2[] = { 5.0, -5.0, 0.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT2, GL_POSITION, position2);

    gluLookAt(	//
            0.0, 0.0, 10.0, // eye
            0.0, 0.0, 0.0, // center
            0.0, 1.0, 0.0 // up
            );
}

/**
 * {@inheritDoc}
 */
void updateEquation(void){
    // TODO updateEquation in mainwindow
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH00(double value){
    this->matCollineation[0][0] = value;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH01(double value){
    this->matCollineation[0][1] = value;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH02(double value){
    this->matCollineation[0][2] = value;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH10(double value){
    this->matCollineation[1][0] = value;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH11(double value){
    this->matCollineation[1][1] = value;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH12(double value){
    this->matCollineation[1][2] = value;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH20(double value){
    this->matCollineation[2][0] = value;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH21(double value){
    this->matCollineation[2][1] = value;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH22(double value){
    this->matCollineation[2][2] = value;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH30(double value){
    this->matCollineation[3][0] = value;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH31(double value){
    this->matCollineation[3][1] = value;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH32(double value){
    this->matCollineation[3][2] = value;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setH33(double value){
    this->matCollineation[3][3] = value;
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::zoom(int value){
    if (this->zoomValue > value) {
        this->zoomOut();
    } else {
        this->zoomIn();
    }
    this->zoomValue = value;
    this->updateGL();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::up(){
    glRotatef(-rotateValue, 1.0, 0.0, 0.0);
    this->updateGL();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::down(){
    glRotatef(rotateValue, 1.0, 0.0, 0.0);
    this->updateGL();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::left(){
    glRotatef(-rotateValue, 0.0, 1.0, 0.0);
    this->updateGL();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::right(){
    glRotatef(rotateValue, 0.0, 1.0, 0.0);
    this->updateGL();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setPerspectivicProjection(bool state){
    if (state) {
        this->projectionType = PERSPECIVIC;
    } else {
        this->projectionType = ORTHOGRAPHIC;
    }
    this->updateGL();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setStereoscope(bool state){
    this->STEREOSCOPE_DRAW = state;
    this->updateGL();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setWireframe(bool state){
    this->WIREFRAME_MODE = state;
    this->updateGL();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::setOrientation(bool state){
    this->ORIENTATION_DRAW = state;
    this->updateGL();
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::zoomIn(){
    glScalef(zoomInValue, zoomInValue, zoomInValue);
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::zoomOut(){
    glScalef(zoomOutValue, zoomOutValue, zoomOutValue);
}

/**
 * {@inheritDoc}
 */
void QirGLWidget::drawOrientation(GLfloat scale) {

    // Bodengitter
    glColor4fv(GREY);
    glBegin(GL_LINES);
    int lines = 3;
    for (int i = -lines; i < (lines + 1); i++) {
        // x
        glVertex3f(scale / lines * i, -scale, -1.0);
        glVertex3f(scale / lines * i, scale, -1.0);
        // y
        glVertex3f(-scale, scale / lines * i, -1.0);
        glVertex3f(scale, scale / lines * i, -1.0);
    }
    glEnd();


    if (this->WIREFRAME_MODE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDisable(GL_CULL_FACE);
    }


    // x-axis
    if (this->STEREOSCOPE_DRAW) {
        glColor4fv(GREY);
    } else {
        glColor4fv(RED);
    }
    glPushMatrix();
    glRotatef(90, 0.0, 1.0, 0.0);
    glutSolidCylinder(scale * 0.01, scale, 10, 1);
    glPopMatrix();
    //
    glPushMatrix();
    glTranslatef(scale, 0.0, 0.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glutSolidCone(scale * 0.025, scale * 0.2, 10, 1);
    glPopMatrix();

    // y-axis
    if (this->STEREOSCOPE_DRAW) {
        glColor4fv(GREY);
    } else {
        glColor4fv(GREEN);
    }
    glPushMatrix();
    glRotatef(90, -1.0, 0.0, 0.0);
    glutSolidCylinder(scale * 0.01, scale, 10, 1);
    glPopMatrix();
    //
    glPushMatrix();
    glTranslatef(0.0, scale, 0.0);
    glRotatef(90, -1.0, 0.0, 0.0);
    glutSolidCone(scale * 0.025, scale * 0.2, 10, 1);
    glPopMatrix();

    // z-axis
    if (this->STEREOSCOPE_DRAW) {
        glColor4fv(GREY);
    } else {
        glColor4fv(BLUE);
    }
    glPushMatrix();
    glutSolidCylinder(scale * 0.01, scale, 10, 1);
    glPopMatrix();
    //
    glPushMatrix();
    glTranslatef(0.0, 0.0, scale);
    glutSolidCone(scale * 0.025, scale * 0.2, 10, 1);
    glPopMatrix();

    if (this->WIREFRAME_MODE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_CULL_FACE);
    }

    glFlush();
}


void QirGLWidget::initGeometry(void) {

    /**
     * Create display lists,
     * each with a different quadric object.
     */
    GLsizei range = NUMBER_OF_FIGURES * NUMBER_OF_ENTRIES_PER_FIGURE;
    startList = glGenLists(range);
    GLuint offset = 0;

    // Basic setup
    GLUquadricObj *qObject;
    qObject = gluNewQuadric();
    gluQuadricCallback(qObject, GLU_ERROR, this->errorCallback);
    gluQuadricOrientation(qObject, GLU_OUTSIDE); // GLU_OUTSIDE or GLU_INSIDE

    /* Mittelpunktsquadrik */
    // Bounding-Box
    glNewList(startList + offset++, GL_COMPILE);
    glutWireCube(2.0);
    glEndList();
    // Festkörper
    gluQuadricDrawStyle(qObject, GLU_FILL); // smooth shaded
    gluQuadricNormals(qObject, GL_SMOOTH); // GL_FLAT or GL_SMOOTH
    glNewList(startList + offset++, GL_COMPILE);
    gluSphere(qObject, 1.0, 40, 20);
    glEndList();
    // Drahtkörper
    gluQuadricDrawStyle(qObject, GLU_LINE); // wireframe
    gluQuadricNormals(qObject, GLU_NONE);
    glNewList(startList + offset++, GL_COMPILE);
    gluSphere(qObject, 1.0, 40, 20);
    glEndList();
    // Umrandung
    /**
     gluQuadricDrawStyle(qObject, GLU_SILHOUETTE); // silhouette
     gluQuadricNormals(qObject, GLU_NONE);
     glNewList(startList + offset++, GL_COMPILE);
     gluSphere(qObject, 1.0, 40, 20);
     glEndList();
     */

    /* Parabolischer Typ */
    // Bounding-Box
    glNewList(startList + offset++, GL_COMPILE);
    glutWireCube(2.0);
    glEndList();
    // Festkörper
    gluQuadricDrawStyle(qObject, GLU_FILL); // smooth shaded
    gluQuadricNormals(qObject, GL_SMOOTH); // GL_FLAT or GL_SMOOTH
    glNewList(startList + offset++, GL_COMPILE);
    gluDisk(qObject, 0.0, 1.0, 40, 20);
    glEndList();
    // Drahtkörper
    gluQuadricDrawStyle(qObject, GLU_LINE); // wireframe
    gluQuadricNormals(qObject, GLU_NONE);
    glNewList(startList + offset++, GL_COMPILE);
    gluDisk(qObject, 0.0, 1.0, 40, 20);
    glEndList();
    // Umrandung
    /**
     gluQuadricDrawStyle(qObject, GLU_SILHOUETTE); // silhouette
     gluQuadricNormals(qObject, GLU_NONE);
     glNewList(startList + offset++, GL_COMPILE);
     gluDisk(qObject, 0.0, 1.0, 40, 20);
     glEndList();
     */

    /* Kegeliger Typ */
    // Bounding-Box
    glNewList(startList + offset++, GL_COMPILE);
    glutWireCube(2.0);
    glEndList();
    // Festkörper
    gluQuadricDrawStyle(qObject, GLU_FILL); // smooth shaded
    gluQuadricNormals(qObject, GL_SMOOTH); // GL_FLAT or GL_SMOOTH
    glNewList(startList + offset++, GL_COMPILE);
    gluCylinder(qObject, 1.0, 1.0, 2.0, 40, 20);
    glEndList();
    // Drahtkörper
    gluQuadricDrawStyle(qObject, GLU_LINE); /* wireframe */
    gluQuadricNormals(qObject, GLU_NONE);
    glNewList(startList + offset++, GL_COMPILE);
    gluCylinder(qObject, 1.0, 1.0, 2.0, 40, 20);
    glEndList();
    // Umrandung
    /**
     gluQuadricDrawStyle(qObject, GLU_SILHOUETTE); // silhouette
     gluQuadricNormals(qObject, GLU_NONE);
     glNewList(startList + offset++, GL_COMPILE);
     gluCylinder(qObject, 1.0, 0.0, 2.0, 40, 20);
     glEndList();
     */

    /* Teeiger Typ */
    // Bounding-Box
    glNewList(startList + offset++, GL_COMPILE);
    glutWireCube(2.0);
    glEndList();
    // Festkörper
    gluQuadricDrawStyle(qObject, GLU_FILL); // smooth shaded
    gluQuadricNormals(qObject, GL_SMOOTH); // GL_FLAT or GL_SMOOTH
    glNewList(startList + offset++, GL_COMPILE);
    glutSolidTeapot(1.0);
    glEndList();
    // Drahtkörper
    gluQuadricDrawStyle(qObject, GLU_LINE); // wireframe
    gluQuadricNormals(qObject, GLU_NONE);
    glNewList(startList + offset++, GL_COMPILE);
    glutWireTeapot(1.0);
    glEndList();
    // Umrandung
    /**
     gluQuadricDrawStyle(qObject, GLU_SILHOUETTE); // silhouette
     gluQuadricNormals(qObject, GLU_NONE);
     glNewList(startList + offset++, GL_COMPILE);
     glutWireTeapot(1.0);
     glEndList();
     */

    // tear down
    // gluDeleteQuadric(qObject);
}


/**
 * {@inheritDoc}
 */
void QirGLWidget::drawGeometry(int type) {

}
