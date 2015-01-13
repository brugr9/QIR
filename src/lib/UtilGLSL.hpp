/*/////////////////////////////////////////////////////////////////////////////////////////////////
module:  Declaration of GLSL utility class
purpose: Implements general utilities for GLSL support

written: U.Kuenzler
version: 1.10
/////////////////////////////////////////////////////////////////////////////////////////////////*/


// system includes ////////////////////////////////////////////////////////////////////////////////
#include <string>


class UtilGLSL
///////////////////////////////////////////////////////////////////////////////////////////////////
{
public:
	static void   showOpenGLVersion(void);
	static void   showGLSLVersion(void);
	static float  checkOpenGLVersion(void);
	static void   checkGLSLVersion(GLint *major, GLint *minor);
	static void   initOpenGLDebugCallback(void);
	static void   checkOpenGLErrorCode(void);
	static void   checkShaderInfoLog(GLuint shader);
	static void   checkProgramInfoLog(GLuint program);
	static GLuint initShaderProgram(int argc, char **argv);

private:
    static char*  readShaderFile(const string& filename);
	static void   DebugMessageCallback(GLenum source, GLenum type, GLuint id,
					GLenum severity, GLsizei length, const GLchar* message,	void* userParam);
};
// class UtilGLSL /////////////////////////////////////////////////////////////////////////////////
