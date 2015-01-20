/**
 * GLUT perspective methods declaration,
 * adapted for the QIR application.
 *
 * @author Roland Bruggmann
 */

/**
 * @brief A three dimension vector.
 */
typedef struct {
   double x,y,z;
} XYZ;

/**
 * @brief A camera value container.
 *
 * <ul>
 * <li> vp: View position
 * <li> vd: View direction vector
 * <li> vu: View up direction
 * <li> pr: Point to rotate about
 * <li> focallength: Focal Length along vd
 * <li> aperture: Camera aperture
 * <li> eyesep: Eye separation
 * <li> sheight: screenheight
 * <li> swidth: screenwidth
 * </ul>
 */
typedef struct {
   XYZ vp;               /* View position           */
   XYZ vd;               /* View direction vector   */
   XYZ vu;               /* View up direction       */
   XYZ pr;               /* Point to rotate about   */
   double focallength;   /* Focal Length along vd   */
   double aperture;      /* Camera aperture         */
   double eyesep;        /* Eye separation          */
   int sheight, swidth;  /* screenheight,screenwidth*/
} CAMERA;

/**
 * @brief Move the camera to the home position or to a predefined stereo configuration.
 * The model is assumed to be in a 10x10x10 cube centered at the origin.
 *
 * @param camera Pointer to the camera to initialize.
 * @param mode The mode to set.
 */
void initCamera(CAMERA *camera, int mode);

/**
 * @brief Normalizes a given vector.
 *
 * @param p The pointer to the vector.
 */
void normalise(XYZ *p);

/**
 * @brief Calculates the cross product.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param v3pointer Pointer to the third vector.
 */
void crossProd(XYZ v1, XYZ v2, XYZ *v3pointer);
