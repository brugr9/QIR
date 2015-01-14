/**
 * GLUT animation methods implementation.
 *
 * @author Roland Bruggmann
 */

#include "qirglutanimation.h"
#include "lib/OpenGL.h"

/**
 * @brief A field for the animation running state.
 */
bool ANIMATION_RUNNING = false;

/**
 * @brief A field for the animation speed.
 */
unsigned int TIME = 30;

/**
 * @brief Simply rotates the scene (z-axis).
 *
 * @param timer_id Timer ID used for GLUT timer function.
 */
void animation(int timer_id) {
    // rotation (z-axis)
    glRotatef(1.0, 0.0, 0.0, 1.0);
    // redraw the scene
    glutPostRedisplay();
    // reset timer if the animation is running
    if (ANIMATION_RUNNING)
        glutTimerFunc(TIME, animation, 0);
}

/**
 * {@inheritDoc}
 */
void startAnimation(void) {
    glutTimerFunc(TIME, animation, 0);
    ANIMATION_RUNNING = true;
}

/**
 * {@inheritDoc}
 */
void stopAnimation(void) {
    glutIdleFunc(NULL);
    ANIMATION_RUNNING = false;
}

/**
 * {@inheritDoc}
 */
void handleAnimation(void){
    if (ANIMATION_RUNNING) {
        stopAnimation();
    } else {
        startAnimation();
    }
}
