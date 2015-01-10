#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "lib/OpenGL.h"
#include <QGLWidget>
#include <QMouseEvent>

/**
 *
 */
typedef struct {
   double x,y,z;
} XYZ;

/**
 *
 */
typedef struct {
   XYZ vp;              /* View position           */
   XYZ vd;              /* View direction vector   */
   XYZ vu;              /* View up direction       */
   XYZ pr;              /* Point to rotate about   */
   double focallength;  /* Focal Length along vd   */
   double aperture;     /* Camera aperture         */
   double eyesep;       /* Eye separation          */
   int sheight,swidth;  /* screenheight,screenwidth*/
} CAMERA;

/**
 * @brief An OpenGL-Widget for the QIR application.
 */
class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    /**
     * @brief Main constructor.
     * @param parent
     */
    explicit MyGLWidget(QWidget *parent = 0);
    /**
     * @brief Destructor.
     */
    ~MyGLWidget();

    void setH00(double arg);
    void setH01(double arg);
    void setH02(double arg);

    void setH10(double arg);
    void setH11(double arg);
    void setH12(double arg);

    void setH20(double arg);
    void setH21(double arg);
    void setH22(double arg);

    void setH30(double arg);
    void setH31(double arg);
    void setH32(double arg);
    void setH33(double arg);

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
     * @param width The widget width.
     * @param height The widget height.
     */
    void resizeGL(int width, int height);

private:

    /**
     * @brief homographyMat4
     */
    mat4 homographyMat4;
    /**
     * @brief coefficientsMat4
     */
    mat4 coefficientsMat4;
    /**
     * @brief draw
     */
    void draw(void);
};

#endif // MYGLWIDGET_H
