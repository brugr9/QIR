/**
 * GLUT mouse methods implementation,
 * adapted for the QIR application.
 *
 * @author Roland Bruggmann
 */

#include "qirglutmouse.h"
#include "qirmodel.h"

#include <string>
#include "lib/OpenGL.h"

/**
 * @brief A field for a mouse menu entry value.
 */
int MENU_ENTRY = 0;

/**
 * @brief A field for a mouse menu value.
 */
int MENU_VALUE = 0;

/**
 * @brief A field for a mouse menu name.
 */
string MENU_NAME;


/**
 * {@inheritDoc}
 */
void initMenu() {

    // create menu
    glutCreateMenu(qirMenu);
    glutAddMenuEntry("Orientierung aus", 1);
    glutAddMenuEntry("Bounding-Box an", 2);
    glutAddMenuEntry("Drahtgitter-Modus an", 3);

    // attach menu to right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
 * {@inheritDoc}
 */
void qirMenu(int item) {

    switch (item) {
    case 1: {
        qType = QTYPE_CENTRIC;
        break;
    }
    case 2: {
        qType = QTYPE_CONIC;
        break;
    }
    case 3: {
        qType = QTYPE_PARABOLIC;
        break;
    }
    case 4: {
        qType = QTYPE_TEEINE;
        break;
    }
    case 5: {
        // --
        break;
    }
    case 6: {
        if (AXIS_DRAW) {
            initMenuChange(6, "Orientierung an", 6);
        } else {
            initMenuChange(6, "Orientierung aus", 6);
        }
        AXIS_DRAW = !AXIS_DRAW;
        break;
    }
    case 7: {
        if (BOUNDING_BOX) {
            initMenuChange(7, "Bounding-Box an", 7);
        } else {
            initMenuChange(7, "Bounding-Box aus", 7);
        }
        BOUNDING_BOX = !BOUNDING_BOX;
        break;
    }
    case 8: {
        if (WIREFRAME_MODE) {
            initMenuChange(8, "Drahtgitter-Modus an", 8);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDisable(GL_CULL_FACE);
        } else {
            initMenuChange(8, "Drahtgitter-Modus aus", 8);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glEnable(GL_CULL_FACE);
            //glDisable(GL_CULL_FACE); transparency TODO
        }
        WIREFRAME_MODE = !WIREFRAME_MODE;
        break;
    }
    case 9: {
        // --
        break;
    }
    case 10: {
        if (PERSPECTIVE_DRAW) {
            initMenuChange(10, "Perspektivische Projektion", 10);
        } else {
            initMenuChange(10, "Orthografische Projektion", 10);
        }
        PERSPECTIVE_DRAW = !PERSPECTIVE_DRAW;
        // resizeGL(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
    }
    case 11: {
        if (STEREOSCOPE_DRAW) {
            initMenuChange(11, "Stereobildwidergabe an", 11);
        } else {
            initMenuChange(11, "Stereobildwidergabe aus", 11);
        }
        STEREOSCOPE_DRAW = !STEREOSCOPE_DRAW;
        // resizeGL(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        break;
    }
    case 12: {
        // --
        break;
    }

        break;
    }
    default: {
        // reset settings
    }
    }
    glutPostRedisplay();
}

/**
 * {@inheritDoc}
 */
void initMenuChange(int entry, char *name, int value) {
    MENU_ENTRY = entry;
    MENU_VALUE = value;
    MENU_NAME.assign(name);
}

/**
 * {@inheritDoc}
 */
void updateMenu(int status, int x, int y) {
    if (status == GLUT_MENU_NOT_IN_USE) {
        // menu not in use, time to make changes
        if (MENU_ENTRY < 0) {
            // reset menu to default
            cout << "Resetting Menu..." << endl;
            initMenu();
        } else {
            glutChangeToMenuEntry(MENU_ENTRY, MENU_NAME.c_str(), MENU_VALUE);
        }
    }
}

