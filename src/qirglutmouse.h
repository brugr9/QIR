/**
  * GLUT mouse methods declaration,
  * adapted for the QIR application.
  *
  * @author Roland Bruggmann
  */

/**
 * @brief Initialises the mouse menu.
 * A mouse menu will be attached to the right mouse button.
 */
void initMenu(void);

/**
 * @brief A GLUT mouse menu entry callback handler.
 * @param item The menu item to call.
 */
void qirMenu(int item);

/**
 * @brief A change mouse menu handler.
 * A helper method for a GLUT mouse menu.
 *
 * @param entry
 * @param name A pointer to the name to set.
 * @param value
 */
void initMenuChange(int entry, char *name, int value);

/**
 * @brief A GLUT update mouse menu callback handler.
 * @param status GLUT menu related macro definition
 * @param x
 * @param y
 */
void updateMenu(int status, int x, int y);
