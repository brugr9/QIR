#include "qirmodel.h"
#include "qirglperspective.h"
#include "lib/OpenGL.h"

// global defines
int ARGC = 0;
char** ARGV = 0;
_GLUfuncptr errorCallback;
int PROGRAM_ID = 0;

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
enum QuadricType {
  QTYPE_CENTRIC     = 0,
  QTYPE_PARABOLIC   = 1,
  QTYPE_CONIC       = 2,
  QTYPE_TEEINE      = 3
};

GLuint startList;
const GLuint NUMBER_OF_FIGURES = 4;
const GLuint NUMBER_OF_ENTRIES_PER_FIGURE = 3;
bool BOUNDING_BOX = false;

// Koeffizientenmatrize Q
mat4 Q1 = mat4( //
        0.0f, 0.0f, 0.0f, 0.0f, // col 1
        0.0f, 0.0f, 0.0f, 0.0f, // col 2
        0.0f, 0.0f, 0.0f, 0.0f, // col 3
        0.0f, 0.0f, 0.0f, 0.0f  // col 4
        );
// Projektive Transformation H
mat4 H(1.0);
// Koeffizientenmatrize Q'
mat4 Q2 = mat4(  //
        0.0f, 0.0f, 0.0f, 0.0f, // col 1
        0.0f, 0.0f, 0.0f, 0.0f, // col 2
        0.0f, 0.0f, 0.0f, 0.0f, // col 3
        0.0f, 0.0f, 0.0f, 0.0f  // col 4
        );


// Navigation
bool AXIS_DRAW = true;

// Projektion
const int PTYPE_ORTHOGRAPHIC = 0;
const int PTYPE_PERSPECTIVIC = 1;
bool PERSPECTIVE_DRAW = false;
bool STEREOSCOPE_DRAW = false;
bool WIREFRAME_MODE = false;
CAMERA camera; // stereo
