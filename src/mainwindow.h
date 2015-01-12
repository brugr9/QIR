#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myglwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    /**
     * @brief Konstruktor.
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief Destuktor.
     */
    ~MainWindow();

private slots:

    //////////////////////////////////////////////////
    //// Menu
    //////////////////////////////////////////////////

    /**
     * @brief Mittelpunktsquadrik gewählt.
     */
    void on_actionMittelpunktsquadrik_triggered();

    /**
     * @brief Kegeliger Typ gewählt.
     */
    void on_actionKegeliger_Typ_triggered();

    /**
     * @brief Parabolischer Typ gewählt.
     */
    void on_actionParabolischer_Typ_triggered();

    /**
     * @brief Ellipsoid gewählt.
     */
    void on_actionEllipsoid_triggered();

    /**
     * @brief Hyperboloid, einschalig gewählt.
     */
    void on_actionHyperboloidEinschalig_triggered();

    /**
     * @brief Hyperboloid, zweischalig gewählt.
     */
    void on_actionHyperboloidZweischalig_triggered();

    /**
     * @brief Paraboloid, elliptisch gewählt.
     */
    void on_actionParaboloidElliptisch_triggered();

    /**
     * @brief Paraboloid, hyperbolisch gewählt.
     */
    void on_actionParaboloidHyperbolisch_triggered();

    /**
     * @brief Exit application gewählt.
     */
    void on_actionBeenden_triggered();

    /**
     * @brief Info gewählt.
     */
    void on_actionInfo_triggered();

    //////////////////////////////////////////////////
    //// Transformation
    //////////////////////////////////////////////////


    /**
     * @brief Transformation: h11 geändert.
     * @param arg1
     */
    void on_doubleSpinBox_11_valueChanged(double arg1);
    /**
      * @brief Transformation: h12 geändert.
     * @param arg1
     */
    void on_doubleSpinBox_12_valueChanged(double arg1);
    /**
      * @brief Transformation: h13 geändert.
     * @param arg1
     */
    void on_doubleSpinBox_13_valueChanged(double arg1);
    /**
      * @brief Transformation: h21 geändert.
     * @param arg1
     */
    void on_doubleSpinBox_21_valueChanged(double arg1);
    /**
      * @brief Transformation: h22 geändert.
     * @param arg1
     */
    void on_doubleSpinBox_22_valueChanged(double arg1);
    /**
      * @brief Transformation: h23 geändert.
     * @param arg1
     */
    void on_doubleSpinBox_23_valueChanged(double arg1);
    /**
      * @brief Transformation: h31 geändert.
     * @param arg1
     */
    void on_doubleSpinBox_31_valueChanged(double arg1);
    /**
      * @brief Transformation: h32 geändert.
     * @param arg1
     */
    void on_doubleSpinBox_32_valueChanged(double arg1);
    /**
      * @brief Transformation: h32 geändert.
     * @param arg1
     */
    void on_doubleSpinBox_33_valueChanged(double arg1);
    /**
      * @brief Transformation: h41 geändert.
     * @param arg1
     */
    void on_doubleSpinBox_41_valueChanged(double arg1);
    /**
      * @brief Transformation: h42 geändert.
     * @param arg1
     */
    void on_doubleSpinBox_42_valueChanged(double arg1);
    /**
      * @brief Transformation: h43 geändert.
     * @param arg1
     */
    void on_doubleSpinBox_43_valueChanged(double arg1);
    /**
      * @brief Transformation: h44 geändert.
     * @param arg1
     */
    void on_doubleSpinBox_44_valueChanged(double arg1);


    //////////////////////////////////////////////////
    //// Navigation
    //////////////////////////////////////////////////

    /**
      * @brief Zoom-Slider geändert.
     * @param value Zoom-Wert, der angezeigt werden soll.
     */
    void on_verticalSlider_zoom_valueChanged(int value);

    /**
      * @brief Hoch-Druckknopf geklickt.
     */
    void on_toolButton_up_clicked();

    /**
      * @brief Runter-Druckknopf geklickt.
     */
    void on_toolButton_down_clicked();

    /**
      * @brief Links-Druckknopf geklickt.
     */
    void on_toolButton_left_clicked();

    /**
      * @brief Rechts-Druckknopf geklickt.
     */
    void on_toolButton_right_clicked();

    //////////////////////////////////////////////////
    //// Projektion
    //////////////////////////////////////////////////

    /**
     * @brief Orthografische Projektion gewählt.
     * @param checked
     */
    void on_radioButton_orthograficProjektion_toggled(bool checked);

    /**
      * @brief Perspektivische Projektion gewählt.
     * @param checked
     */
    void on_radioButton_projectivicProjektion_toggled(bool checked);

    /**
      * @brief Stereobildwidergabe gewählt.
     * @param checked
     */
    void on_checkBox_stereo_toggled(bool checked);

private:
    /**
     * @brief A field for the graphic user interface: Main window.
     */
    Ui::MainWindow *ui;

    /**
     * @brief A field for the graphic user interface: About window.
     */
    QDialog *about;

    /**
     * @brief A field for a MyGLWidget.
     */
    MyGLWidget myGLWidget;

    /**
     * @brief Werte der Koeffizientenmatrize setzen.
     * @param a Koeffizient a
     * @param b Koeffizient b
     * @param c Koeffizient c
     * @param f Koeffizient f
     * @param g Koeffizient g
     * @param h Koeffizient h
     * @param p Koeffizient p
     * @param q Koeffizient q
     * @param r Koeffizient r
     * @param d Koeffizient d
     */
    void setCoefficients(double a, double b, double c, double f, double g, double h, double p, double q, double r, double d);

    /**
     * @brief Werte der Kollineationsmatrize setzen.
     * @param h11
     * @param h12
     * @param h13
     * @param h21
     * @param h22
     * @param h23
     * @param h31
     * @param h32
     * @param h33
     * @param h41
     * @param h42
     * @param h43
     * @param h44
     */
    void setHomography(//
            float h11, float h12, float h13, // Zeile 1
            float h21, float h22, float h23, // Zeile 2
            float h31, float h32, float h33, // Zeile 3
            float h41, float h42, float h43, float h44 // Zeile 4
            );

    /**
      * @brief Koordinatengleichung ax^2 + by^2 + cz^2 + 2fyz + 2gzx + 2hxy + 2px + 2qy + 2rz + d = 0 aktualisieren.
     */
    void updateEquation(void);

};

#endif // MAINWINDOW_H
