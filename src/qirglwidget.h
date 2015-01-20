#ifndef QIRGLWIDGET_H
#define QIRGLWIDGET_H

#include <QGLWidget>
#include "lib/OpenGL.h"

// GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // initializeGL
#include <glm/gtc/type_ptr.hpp> // initializeGL
#include <glm/gtc/constants.hpp> // initializeGL
using namespace glm;

namespace Qir {
class QirGLWidget;
}

/**
 * @brief The PROJECTION_TYPE enum
 */
enum PROJECTION_TYPE{
    PERSPECIVIC = 0x000,
    ORTHOGRAPHIC = 0x001
};

/**
 * @brief The QUADRIC_TYPE enum
 */
enum QUADRIC_TYPE {
    CENTRIC = 0,
    CONIC = 2,
    PARABOLIC = 1,
    TEEINE = 3
};

/**
 * @brief An OpenGL-Widget for the QIR application.
 */
class QirGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    /**
     * @brief Main constructor.
     * @param parent
     */
    explicit QirGLWidget(QWidget *parent = 0);
    /**
     * @brief Destructor.
     */
    ~QirGLWidget();

private:

    /**
     * @brief qType
     */
    QUADRIC_TYPE qType;

    /**
     * @brief A field for a collineation matrix.
     */
    mat4 matCollineation;

    /**
     * @brief A field for a zoom value.
     */
    int zoomValue;

    /**
     * @brief A field for a zoom in value greater then one.
     */
    GLfloat zoomInValue;

    /**
     * @brief A field for a zoom out value smaller then one.
     */
    GLfloat zoomOutValue;

    /**
     * @brief A field for rotate value.
     */
    GLfloat rotateValue;

    /**
     * @brief A field for a projection type.
     */
    PROJECTION_TYPE projectionType;

    /**
     * @brief A field for a stereoscope draw state.
     */
    bool STEREOSCOPE_DRAW;

    /**
     * @brief A field for a wireframe mode state.
     */
    bool WIREFRAME_MODE;

    /**
     * @brief A field for a orientation draw state.
     */
    bool ORIENTATION_DRAW;

    /**
     * @brief A field for a bounding box draw state.
     */
    bool BOUNDING_BOX;

    /**
     * @brief A field for a camera.
     */
    // CAMERA camera;

    /**
     * @brief errorCallback
     */
    _GLUfuncptr errorCallback;

signals:


public slots:

    /**
     * @brief setQuadricType
     * @param type The type to set.
     */
    void setQuadricType(QUADRIC_TYPE type);

    /**
     * @brief setH00
     * @param value The value to set.
     */
    void setH00(double value);
    /**
     * @brief setH01
     * @param value
     */
    void setH01(double value);
    /**
     * @brief setH02
     * @param value
     */
    void setH02(double value);
    /**
     * @brief setH10
     * @param value
     */
    void setH10(double value);
    /**
     * @brief setH11
     * @param value
     */
    void setH11(double value);
    /**
     * @brief setH12
     * @param value
     */
    void setH12(double value);
    /**
     * @brief setH20
     * @param value
     */
    void setH20(double value);
    /**
     * @brief setH21
     * @param value
     */
    void setH21(double value);
    /**
     * @brief setH22
     * @param value
     */
    void setH22(double value);
    /**
     * @brief setH30
     * @param value
     */
    void setH30(double value);
    /**
     * @brief setH31
     * @param value
     */
    void setH31(double value);
    /**
     * @brief setH32
     * @param value
     */
    void setH32(double value);
    /**
     * @brief setH33
     * @param value
     */
    void setH33(double value);

    /**
     * @brief Zoom in or out to the value as given.
     */
    void zoom(int value);
    /**
     * @brief Rotate up (increase x-axis rotation).
     */
    void up(void);
    /**
     * @brief Rotate down (decrease x-axis rotation).
     */
    void down(void);
    /**
     * @brief Rotate left (increase y-axis rotation).
     */
    void left(void);
    /**
     * @brief Rotate right (decrease y-axis rotation).
     */
    void right(void);

    /**
     * @brief setPerspectivicProjection
     */
    void setPerspectivicProjection(bool state);
    /**
     * @brief setStereoscope
     */
    void setStereoscope(bool state);
    /**
     * @brief setWireframe
     */
    void setWireframe(bool state);
    /**
     * @brief setOrientation
     */
    void setOrientation(bool state);
    /**
     * @brief setBoundingBox
     */
    void setBoundingBox(bool state);

protected:

    /**
     * @brief Initializes the widget: will be called to initialize the GL Context.
     */
    void initializeGL();

    /**
     * @brief Paints the widget: will be called when the OpenGL widget needs to be redrawn.
     */
    void paintGL();

    /**
     * @brief Resizes the widget: will be called when the widget is resized.
     *
     * @param width The widget width.
     * @param height The widget height.
     */
    void resizeGL(int width, int height);


    // void mousePressEvent(QMouseEvent *);

    // void keyPressEvent(QKeyEvent *);

private:

    /**
     * @brief Zoom in.
     */
    void zoomIn(void);

    /**
     * @brief Zoom out.
     */
    void zoomOut(void);

    // QTimer animation();

    /**
     * @brief Initialises the geometry.
     *
     *
     * Quadrics (see Redbook v1.1).
     *
     *
     * Specify the rendering attributes for the object
     * - Use gluQuadricOrientation() to differentiate the
     * interior from the exterior
     * - Use gluQuadricDrawStyle() to render as points,
     * lines or filled polygons
     * - Use gluQuadricNormal() to specify how surface
     * normals should be generated
     * - Use gluQuadricTexture() to generate texture
     * coordinates
     *
     */
    void initGeometry(void);

    /**
     * @brief Draws the geometry.
     * @param type The type of quadric.
     */
    void drawGeometry(int type);

    /**
     * @brief drawOrientation
     * @param scale
     */
    void drawOrientation(GLfloat scale);

    /**
     * @brief draw
     */
    void draw(void);

};

#endif // QIRGLWIDGET_H
