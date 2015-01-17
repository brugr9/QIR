#ifndef QIRGLWIDGET_H
#define QIRGLWIDGET_H

// #include "qirglutkeyboard.h"
// #include "qirglutmouse.h"
#include <QGLWidget>

// GLM
// #define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // initializeGL
#include <glm/gtc/type_ptr.hpp> // initializeGL
#include <glm/gtc/constants.hpp> // initializeGL
using namespace glm;

namespace Qir {
class QirGLWidget;
}

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

    /**
     * @brief setH00
     * @param arg
     */
    void setH00(double arg);
    /**
     * @brief setH01
     * @param arg
     */
    void setH01(double arg);
    /**
     * @brief setH02
     * @param arg
     */
    void setH02(double arg);
    /**
     * @brief setH10
     * @param arg
     */
    void setH10(double arg);
    /**
     * @brief setH11
     * @param arg
     */
    void setH11(double arg);
    /**
     * @brief setH12
     * @param arg
     */
    void setH12(double arg);
    /**
     * @brief setH20
     * @param arg
     */
    void setH20(double arg);
    /**
     * @brief setH21
     * @param arg
     */
    void setH21(double arg);
    /**
     * @brief setH22
     * @param arg
     */
    void setH22(double arg);
    /**
     * @brief setH30
     * @param arg
     */
    void setH30(double arg);
    /**
     * @brief setH31
     * @param arg
     */
    void setH31(double arg);
    /**
     * @brief setH32
     * @param arg
     */
    void setH32(double arg);
    /**
     * @brief setH33
     * @param arg
     */
    void setH33(double arg);
    /**
     * @brief zoomIn
     */
    void zoomIn(void);
    /**
     * @brief zoomOut
     */
    void zoomOut(void);
    /**
     * @brief up
     */
    void up(void);
    /**
     * @brief down
     */
    void down(void);
    /**
     * @brief left
     */
    void left(void);
    /**
     * @brief right
     */
    void right(void);

    /**
     * @brief Draws the geometry.
     * @param type The type of quadric.
     */
    void drawGeometry(int type);

signals:


public slots:


protected:
    /**
     * @brief Initializes the widget.
     */
    void initializeGL();
    /**
     * @brief Paints the widget.
     */
    void paintGL();
    /**
     * @brief Resizes the widget.
     *
     * @param width The widget width.
     * @param height The widget height.
     */
    void resizeGL(int width, int height);

private:

    mat4 matCollineation;

    /**
     * @brief drawAxis
     * @param scale
     */
    void drawAxis(GLfloat scale);

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
     * @brief draw
     */
    void draw(void);

};

#endif // QIRGLWIDGET_H
