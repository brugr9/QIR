#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qirglwidget.h"

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
     * @brief A field for an equation.
     * Gemischt-quadratische Koordinatengleichung der Abbildung mit
     * Koeffizienten aus der Koeffizientenmatrize der Abbildung.
     */
    QString equation;


    /**
     * @brief Werte der Koeffizientenmatrize setzen.
     *
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
    void setCoefficients(//
                         double a, double b, double c, // quadratic coefficients
                         double f, double g, double h, // doubled linear coefficients
                         double p, double q, double r, // single linear coefficients
                         double d); // constant coefficient

    /**
     * @brief Werte der Kollineationsmatrize setzen.
     *
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
