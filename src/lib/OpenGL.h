#ifndef OPENGL_H
#define OPENGL_H

// OpenGL helper includes
#if defined(__APPLE__) && defined(__MACH__)
    #include <GLUT/glut.h>
#else
    #include <GL/glew.h>
    #include <GL/glut.h>
    #include <GL/freeglut_ext.h>
#endif

#endif // OPENGL_H
