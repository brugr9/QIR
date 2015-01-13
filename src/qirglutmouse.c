#include "qirglutmouse.h"
#include <string>
#include "lib/OpenGL.h"

/**
 * @brief A field for a menu entry value.
 */
int MENU_ENTRY = 0;

/**
 * @brief A field for a menu value.
 */
int MENU_VALUE = 0;

/**
 * @brief A field for a menu name.
 */
string MENU_NAME;

/**
 * {@inheritDoc}
 */
void initMenu() {

    // create menu
    glutCreateMenu(menu1);
    glutAddMenuEntry("Mittelpunktsquadrik", 1);
    glutAddMenuEntry("Kegeliger Typ", 2);
    glutAddMenuEntry("Parabolischer Typ", 3);
    glutAddMenuEntry("Teeiger Typ", 4); // TODO
    glutAddMenuEntry("-----------------------------", 5);
    glutAddMenuEntry("Orientierung aus", 6);
    glutAddMenuEntry("Bounding-Box an", 7);
    glutAddMenuEntry("Drahtgitter-Modus an", 8);
    glutAddMenuEntry("-----------------------------", 9);
    glutAddMenuEntry("Perspektivische Projektion", 10); // Projektion: ortho, perspectivic
    glutAddMenuEntry("Stereobildwidergabe an", 11);
    glutAddMenuEntry("-----------------------------", 12);
    glutAddMenuEntry("Animation starten", 13);
    glutAddMenuEntry("-----------------------------", 14);
    glutAddMenuEntry("Programm beenden", 0);

    // attach menu to right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
 * {@inheritDoc}
 */
void menu1(int item) {

    switch (item) {
    case 0: {
        exit(0);
        break;
    }
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
    case 13: {
        if (ANIMATION_RUNNING) {
            initMenuChange(13, "Animation starten", 13);
            stopAnimation();
        } else {
            initMenuChange(13, "Animation stoppen", 13);
            startAnimation();
        }
        break;
    }
    case 14: {
        // --
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
 * Helper method.
 *
 * @param status
 * @param x
 * @param y
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

