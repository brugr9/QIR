/**
 * GLUT perspective methods implementation,
 * adapted for the QIR application.
 *
 * @author Roland Bruggmann
 */

#include "qirglperspective.h"
#include "lib/OpenGL.h"
// #include <cmath>

/**
 * {@inheritDoc}
 */
void initCamera(int mode) {
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
 * {@inheritDoc}
 */
void normalise(XYZ *p) {
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
void crossProd(XYZ v1, XYZ v2, XYZ *v3pointer) {
    v3pointer->x = v1.y * v2.z - v1.z * v2.y;
    v3pointer->y = v1.z * v2.x - v1.x * v2.z;
    v3pointer->z = v1.x * v2.y - v1.y * v2.x;
}


/**
 * {@inheritDoc}
 */
void stereoscope(void) {

    static double matrix[16];
    XYZ eyesep, focus;

    // Determine the focal point
    normalise(&camera.vd);
    focus.x = camera.vp.x + camera.focallength * camera.vd.x;
    focus.y = camera.vp.y + camera.focallength * camera.vd.y;
    focus.z = camera.vp.z + camera.focallength * camera.vd.z;

    // Derive the separation vector for eye separation
    crossProd(camera.vd, camera.vu, &eyesep);
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
    gluPerspective(camera.aperture, camera.swidth / (double) camera.sheight, 0.1, 1000.0);
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
    drawGeometry(qType);
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
    drawGeometry(qType);
    glPopMatrix();
    glFlush();

    //done
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}
