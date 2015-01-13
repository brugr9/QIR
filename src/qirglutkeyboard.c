#include "qirglutkeyboard.h"
#include "lib/OpenGL.h"

/**
 * {@inheritDoc}
 */
void keyboard(unsigned char key, int x, int y) {

    switch (key) {
    case 27: {
        exit(0);
        break;
    }
    case ' ': {
        menu1(13);
        break;
    }
    default: {
        break;
    }
    }
    glutPostRedisplay();
}


/**
 * {@inheritDoc}
 */
void specialkey(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_PAGE_UP: {
        // zoom in
        glScalef(1.02, 1.02, 1.02);
        break;
    }
    case GLUT_KEY_PAGE_DOWN: {
        // zoom out
        glScalef(0.98, 0.98, 0.98);
        break;
    }
    case GLUT_KEY_UP: {
        // -x
        glRotatef(-1.0, 1.0, 0.0, 0.0);
        break;
    }
    case GLUT_KEY_DOWN: {
        // +x
        glRotatef(1.0, 1.0, 0.0, 0.0);
        break;
    }
    case GLUT_KEY_LEFT: {
        // -y
        glRotatef(-1.0, 0.0, 1.0, 0.0);
        break;
    }
    case GLUT_KEY_RIGHT: {
        // +y
        glRotatef(1.0, 0.0, 1.0, 0.0);
        break;
    }
    default: {
        break;
    }
    }

    glutPostRedisplay();

}
