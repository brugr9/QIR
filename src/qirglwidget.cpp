#include "qirglwidget.h"

// system includes
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream> // fps
#include <fstream>
#include <string>
#include <cmath> // stereo
using namespace std;

// OpenGL helper includes
#include "lib/OpenGL.h"
#include "lib/UtilGLUT.hpp"
#include "lib/UtilGLSL.hpp"
#include "lib/zpr.h"
#include <QGLWidget>

// Qt includes
#include <QMouseEvent>

// GLM
// #define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // initializeGL
#include <glm/gtc/type_ptr.hpp> // initializeGL
#include <glm/gtc/constants.hpp> // initializeGL
using namespace glm;

// global defines
int ARGC = 0;
char** ARGV = 0;
_GLUfuncptr errorCallback;

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
// BFH
const GLfloat BFHGREY[] = { 0.41, 0.49, 0.57, 1.0 };
const GLfloat BFHYELLOW[] = { 0.741, 0.494, 0.0, 1.0 };

// Quadrik (qobj)
int qType = 0;
const int QTYPE_CENTRIC = 0;
const int QTYPE_PARABOLIC = 1;
const int QTYPE_CONIC = 2;
const int QTYPE_TEEINE = 3;

GLuint startList;
const GLuint NUMBER_OF_FIGURES = 4;
const GLuint NUMBER_OF_ENTRIES_PER_FIGURE = 3;
bool BOUNDING_BOX = false;

// Koeffizientenmatrize Q
mat4 coefficientsMat4 = mat4( //
        0.0f, 0.0f, 0.0f, 0.0f, // col 1
        0.0f, 0.0f, 0.0f, 0.0f, // col 2
        0.0f, 0.0f, 0.0f, 0.0f, // col 3
        0.0f, 0.0f, 0.0f, 0.0f  // col 4
        );
// Projektive Transformation H
mat4 homographyMat4(0.0);
// Koeffizientenmatrize Q'
mat4 coefficientsAbbMat4 = mat4(  //
        0.0f, 0.0f, 0.0f, 0.0f, // col 1
        0.0f, 0.0f, 0.0f, 0.0f, // col 2
        0.0f, 0.0f, 0.0f, 0.0f, // col 3
        0.0f, 0.0f, 0.0f, 0.0f  // col 4
        );
// Gemischt-quadratische Koordinatengleichung mit Koeffizienten aus Q'
string equation;

// Navigation
bool AXIS_DRAW = true;
GLuint zoom = 5; // [1,9]

// Projektion
const int PTYPE_ORTHOGRAPHIC = 0;
const int PTYPE_PERSPECTIVIC = 1;
bool PERSPECTIVE_DRAW = false;
bool STEREOSCOPE_DRAW = false;
bool WIREFRAME_MODE = false;
CAMERA camera; // stereo

// Animation
bool ANIMATION_RUNNING = false;
int ANIMATION_SPEED = 30;

/**
 * Animation, simply rotates the scene (y-axis).
 *
 * @param timer_id Timer ID used for GLUT timer function.
 */
void animation(int timer_id) {
    glRotatef(1.0, 0.0, 0.0, 1.0);
// redraw the scene
    glutPostRedisplay();
// reset timer if the animation is running
    if (ANIMATION_RUNNING)
        glutTimerFunc(ANIMATION_SPEED, animation, 0);
}

/**
 * Starts the animation.
 */
void startAnimation(void) {
    ANIMATION_RUNNING = true;
    glutTimerFunc(ANIMATION_SPEED, animation, 0);

}

/**
 * Stops the animation.
 */
void stopAnimation(void) {
    ANIMATION_RUNNING = false;
    glutIdleFunc(NULL);
}

/**
 * Frames per second.
 */
void fps(void) {

// calculate frames per second (FPS)
    static int frame = 0;
    static int time = 0;
    static int timebase = 0;
    stringstream fps;

    frame++;
    time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        fps.setf(std::ios::fixed, std::ios::floatfield);
        fps.precision(2);
        fps << "FPS: " << frame * 1000.0 / (time - timebase);
        glutSetWindowTitle((fps.str()).c_str());
        timebase = time;
        frame = 0;
    }
}

/**
 * {@inheritDoc}
 */
MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

// nice grids
    glPolygonOffset(1, 1);
    glEnable(GL_POLYGON_OFFSET_FILL);

// register callbacks
    //glutDisplayFunc(paintGL);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkey);
    glutMenuStatusFunc(updateMenu);
    //glutReshapeFunc(resizeGL);

// init application
    zprInit();
    initMenu();
    initializeGL();
    initCamera(3);

    // UtilGLSL::checkOpenGLErrorCode();

}

/**
 * {@inheritDoc}
 */
MyGLWidget::~MyGLWidget()
{
}

/**
 * {@inheritDoc}
 */
void MyGLWidget::setH00(double arg){
    homographyMat4[0][0] = arg;
}

/**
 * {@inheritDoc}
 */
void MyGLWidget::setH01(double arg){
    homographyMat4[0][1] = arg;
}

/**
 * {@inheritDoc}
 */
void MyGLWidget::setH02(double arg){
    homographyMat4[0][2] = arg;
}

/**
 * {@inheritDoc}
 */
void MyGLWidget::setH10(double arg){
    homographyMat4[1][0] = arg;
}

/**
 * {@inheritDoc}
 */
void MyGLWidget::setH11(double arg){
    homographyMat4[1][1] = arg;
}

/**
 * {@inheritDoc}
 */
void MyGLWidget::setH12(double arg){
    homographyMat4[1][2] = arg;
}

/**
 * {@inheritDoc}
 */
void MyGLWidget::setH20(double arg){
    homographyMat4[2][0] = arg;
}

/**
 * {@inheritDoc}
 */
void MyGLWidget::setH21(double arg){
    homographyMat4[2][1] = arg;
}

/**
 * {@inheritDoc}
 */
void MyGLWidget::setH22(double arg){
    homographyMat4[2][2] = arg;
}

/**
 * {@inheritDoc}
 */
void MyGLWidget::setH30(double arg){
    homographyMat4[3][0] = arg;
}

/**
 * {@inheritDoc}
 */
void MyGLWidget::setH31(double arg){
    homographyMat4[3][1] = arg;
}

/**
 * {@inheritDoc}
 */
void MyGLWidget::setH32(double arg){
    homographyMat4[3][2] = arg;
}

/**
 * {@inheritDoc}
 */
void MyGLWidget::setH33(double arg){
    homographyMat4[3][3] = arg;
}


/**
 * {@inheritDoc}
 */
void MyGLWidget::stereoscope(void) {

    static double matrix[16];
    XYZ eyesep, focus;

    // Determine the focal point
    Normalise(&camera.vd);
    focus.x = camera.vp.x + camera.focallength * camera.vd.x;
    focus.y = camera.vp.y + camera.focallength * camera.vd.y;
    focus.z = camera.vp.z + camera.focallength * camera.vd.z;

    // Derive the separation vector for eye separation
    CrossProd(camera.vd, camera.vu, &eyesep);
    Normalise(&eyesep);
    eyesep.x *= camera.eyesep / 2.0;
    eyesep.y *= camera.eyesep / 2.0;
    eyesep.z *= camera.eyesep / 2.0;

    // Set the back buffer for writing
    glDrawBuffer(GL_BACK);

    // Clear things
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camera.aperture, camera.swidth / (double) camera.sheight,
            0.1, 1000.0);

    glViewport(0, 0, camera.swidth, camera.sheight);

    // store zpr transformation matrix
    glGetDoublev(GL_MODELVIEW_MATRIX, matrix);

    // left eye stereo image
    // Clear depth buffer for left eye image
    glClear(GL_DEPTH_BUFFER_BIT);
    // Left eye filter for RED-green/or/blue glasses
    glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
    // Create the model
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    gluLookAt(camera.vp.x - eyesep.x, camera.vp.y - eyesep.y,
            camera.vp.z - eyesep.z, focus.x, focus.y, focus.z, camera.vu.x,
            camera.vu.y, camera.vu.z);
    glTranslatef(0.0, 0.0, 0.02f);
    glMultMatrixd(matrix);
    if (AXIS_DRAW) {
        drawAxis(1.2);
    }
    drawModel(qType);
    glPopMatrix();
    glFlush();

    // right eye stereo image
    // Clear depth buffer for right eye image
    glClear(GL_DEPTH_BUFFER_BIT);
    // Right eye filter for red-GREEN glasses
    glColorMask(GL_FALSE, GL_TRUE, GL_FALSE, GL_TRUE);
    // Right eye filter for red-BLUE glasses
    // glColorMask(GL_FALSE,GL_FALSE,GL_TRUE,GL_TRUE);
    // Create the model
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    gluLookAt(camera.vp.x + eyesep.x, camera.vp.y + eyesep.y,
            camera.vp.z + eyesep.z, focus.x, focus.y, focus.z, camera.vu.x,
            camera.vu.y, camera.vu.z);
    glTranslatef(0.0, 0.0, 0.02f);
    glMultMatrixd(matrix);
    if (AXIS_DRAW) {
        drawAxis(1.2);
    }
    drawModel(qType);
    glPopMatrix();
    glFlush();

    //done
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}


/**
 * {@inheritDoc}
 */
void MyGLWidget::initializeGL()
{
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
    GLfloat MAT_EMISSION[4];
    GLfloat MAT_SHININESS[4];

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
    //*/

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MAT_AMBIENT);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MAT_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MAT_SPECULAR);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MAT_SHININESS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, MAT_EMISSION);
    //*/

    //* define stationary light source properties
    // TODO how to get 3 sources (CMY)
    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse0[] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse1[] = { 0.55, 0.85, 1.0, 1.0 };
    GLfloat diffuse2[] = { 1.0, 0.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat pos[] = { 1.0, 1.0, 1.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_POSITION, pos);

    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT2, GL_POSITION, pos);
    //*/

    // TODO
    glEnable(GL_LIGHT0);
    // glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHTING);

    initModel();

}



/**
 * {@inheritDoc}
 */
void MyGLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (PERSPECTIVE_DRAW) {
        // Perspektivische Projektion

    } else {
        // Orthografische Projektion

        //initialize viewing values
        glMatrixMode(GL_MODELVIEW);

        // draw
        glPushMatrix();
        // glFrontFace(GL_CW);  // face ordering clockwise (reversed)
        if (AXIS_DRAW) {
            drawAxis(1.2);
        }
        drawModel(qType);
        // glFrontFace(GL_CCW); // face ordering counter clockwise
        glPopMatrix();

    }

    if (STEREOSCOPE_DRAW) {
        // Stereografische Projektion
        stereoscope();
    }

    // finally ...
    // UtilGLUT::showFPS("QIR - ");
    // fps();
    glutSwapBuffers();
    // UtilGLSL::checkOpenGLErrorCode();
}

/**
 * ... from 'instanced'
 * @param width
 * @param height
 */
/**
void resizeInstanced(int width, int height) {
    mat4 projection(1.0);
    mat4 camera(1.0);

    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

    if (PERSPECTIVE_DRAW) {
        // adust perspective projection for new viewport
        GLfloat aspect = (GLfloat) width / (GLfloat) height;

        projection = perspective(79.0f * (pi<float>() / 180.0f),
                aspect, 0.1f, 240.0f);
        camera = lookAt(vec3(0.0, 0.0, 200.0), vec3(0.0),
                vec3(0.0, 1.0, 0.0));
    } else {
        // adust orthographic projection for new viewport
        GLfloat aspect = (GLfloat) width / (GLfloat) height;
        GLfloat left = -120.0, right = 120.0;
        GLfloat bottom = -120.0, top = 120.0;
        GLfloat znear = -120.0, zfar = 120.0;

        if (aspect > 1.0f) {
            left *= aspect;
            right *= aspect;
        } else {
            bottom /= aspect;
            top /= aspect;
        }

        projection = ortho(left, right, bottom, top, znear, zfar);
        camera = lookAt(vec3(0.0), vec3(0.0, 0.0, -1.0),
                vec3(0.0, 1.0, 0.0));
    }

    projection = projection * camera;
    GLint location = glGetUniformLocation(PROGRAM_ID, "matProjection");
    glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(projection));
}
*/


/**
 * {@inheritDoc}
 */
void MyGLWidget::resizeGL(int width, int height)
{

    camera.swidth = width;
    camera.sheight = height;

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

    // UtilGLSL::checkOpenGLErrorCode();

}



/**
 * {@inheritDoc}
 */
void MyGLWidget::drawAxis(GLfloat scale) {

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


    if (WIREFRAME_MODE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDisable(GL_CULL_FACE);
    }


    // x-axis
    if (STEREOSCOPE_DRAW) {
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
    if (STEREOSCOPE_DRAW) {
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
    if (STEREOSCOPE_DRAW) {
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

    if (WIREFRAME_MODE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_CULL_FACE);
    }

    glFlush();
}

/**
 * Quadrics (see Redbook v1.1).
 *
 *
 * Specify the rendering attributes for the object
 * - Use gluQuadricOrientation() to differentiate the
 * interior from the exterior
 * - Use gluQuadricDrawStyle() to render as points,
 * lines or filled polygons
 * - Use gluQuadricNormal() to specify how surface
 * normals should be generated
 * - Use gluQuadricTexture() to generate texture
 * coordinates
 *
 */
void MyGLWidget::initModel(void) {

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
    gluQuadricCallback(qObject, GLU_ERROR, errorCallback);
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
void MyGLWidget::drawModel(int type) {

    GLuint offset = NUMBER_OF_ENTRIES_PER_FIGURE * type;

    //* Bounding-Box
    if (BOUNDING_BOX) {
        glColor4fv(GREY);
        glCallList(startList + offset);
    }

    if (type == QTYPE_CONIC) {
        glTranslatef(0.0, 0.0, -1.0);
    }

    //* Festkörper
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH); // GL_FLAT or GL_SMOOTH
    glCallList(startList + ++offset);
    glDisable(GL_LIGHTING);

    //* Drahtkörper
    glColor3f(0.0, 0.0, 0.0); // black
    glCallList(startList + ++offset);

}

/**
 * Move the camera to the home position
 * Or to a predefined stereo configuration
 * The model is assumed to be in a 10x10x10 cube
 * Centered at the origin
 *
 * @param mode
 */
void MyGLWidget::initCamera(int mode) {
    camera.aperture = 60;
    camera.pr.x = 0.0;
    camera.pr.y = 0.0;
    camera.pr.z = 0.0;

    camera.vd.x = 0;
    camera.vd.y = 0;
    camera.vd.z = -1;

    camera.vu.x = 0;
    camera.vu.y = 1;
    camera.vu.z = 0;

    camera.vp.x = 0;
    camera.vp.y = 0;
    camera.vp.z = 10;

    switch (mode) {
    case 0:
    case 2:
    case 4:
        camera.focallength = 10;
        break;
    case 1:
        camera.focallength = 5;
        break;
    case 3:
        camera.focallength = 15;
        break;
    }

    // Non stressful stereo setting
    camera.eyesep = camera.focallength / 30.0;
    if (mode == 4)
        camera.eyesep = 0;
}

/**
 * Normalizes a given vector.
 * @param p Pointer to vector
 */
void MyGLWidget::Normalise(XYZ *p) {
    double length;

    length = sqrt(p->x * p->x + p->y * p->y + p->z * p->z);
    if (length != 0) {
        p->x /= length;
        p->y /= length;
        p->z /= length;
    } else {
        p->x = 0;
        p->y = 0;
        p->z = 0;
    }
}


/**
 * {@inheritDoc}
 */
void MyGLWidget::CrossProd(XYZ p1, XYZ p2, XYZ *p3) {
    p3->x = p1.y * p2.z - p1.z * p2.y;
    p3->y = p1.z * p2.x - p1.x * p2.z;
    p3->z = p1.x * p2.y - p1.y * p2.x;
}
