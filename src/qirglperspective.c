/**
 * GLUT perspective methods implementation,
 * adapted for the QIR application.
 *
 * @author Roland Bruggmann
 */

#include "qirglperspective.h"
#include <math.h>

/**
 * {@inheritDoc}
 */
void initCamera(CAMERA *camera, int mode) {
    camera->aperture = 60;
    camera->pr.x = 0.0;
    camera->pr.y = 0.0;
    camera->pr.z = 0.0;

    camera->vd.x = 0;
    camera->vd.y = 0;
    camera->vd.z = -1;

    camera->vu.x = 0;
    camera->vu.y = 1;
    camera->vu.z = 0;

    camera->vp.x = 0;
    camera->vp.y = 0;
    camera->vp.z = 10;

    switch (mode) {
    case 0:
    case 2:
    case 4:
        camera->focallength = 10;
        break;
    case 1:
        camera->focallength = 5;
        break;
    case 3:
        camera->focallength = 15;
        break;
    }

    // Non stressful stereo setting
    camera->eyesep = camera->focallength / 30.0;
    if (mode == 4)
        camera->eyesep = 0;
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
