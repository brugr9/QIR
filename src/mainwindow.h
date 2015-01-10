#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    //////////////////////////////////////////////////
    //// Menu
    //////////////////////////////////////////////////

    /**
     * Mittelpunktsquadrik
     * @brief on_actionMittelpunktsquadrik_triggered
     */
    void on_actionMittelpunktsquadrik_triggered();

    /**
     * Parabolischer Typ
     * @brief on_actionParabolischer_Typ_triggered
     */
    void on_actionParabolischer_Typ_triggered();

    /**
     * Kegeliger Typ
     * @brief on_actionKegeliger_Typ_triggered
     */
    void on_actionKegeliger_Typ_triggered();

    /**
     * Ellipsoid
     * @brief on_actionEllipsoid_triggered
     */
    void on_actionEllipsoid_triggered();

    /**
     * Hyperboloid, einschalig
     * @brief on_actionHyperboloidEinschalig_triggered
     */
    void on_actionHyperboloidEinschalig_triggered();

    /**
     * Hyperboloid, zweischalig
     * @brief on_actionHyperboloidZweischalig_triggered
     */
    void on_actionHyperboloidZweischalig_triggered();

    /**
     * Paraboloid, elliptisch
     * @brief on_actionParaboloidElliptisch_triggered
     */
    void on_actionParaboloidElliptisch_triggered();

    /**
     * Paraboloid, hyperbolisch
     * @brief on_actionParaboloidHyperbolisch_triggered
     */
    void on_actionParaboloidHyperbolisch_triggered();

    /**
     * Exit application
     * @brief on_actionBeenden_triggered
     */
    void on_actionBeenden_triggered();

    /**
     * Info
     * @brief on_actionInfo_triggered
     */
    void on_actionInfo_triggered();

    //////////////////////////////////////////////////
    //// Transformation
    //////////////////////////////////////////////////


    /**
     * @brief on_doubleSpinBox_11_valueChanged
     * @param arg1
     */
    void on_doubleSpinBox_11_valueChanged(double arg1);
    /**
     * @brief on_doubleSpinBox_12_valueChanged
     * @param arg1
     */
    void on_doubleSpinBox_12_valueChanged(double arg1);
    /**
     * @brief on_doubleSpinBox_13_valueChanged
     * @param arg1
     */
    void on_doubleSpinBox_13_valueChanged(double arg1);
    /**
     * @brief on_doubleSpinBox_21_valueChanged
     * @param arg1
     */
    void on_doubleSpinBox_21_valueChanged(double arg1);
    /**
     * @brief on_doubleSpinBox_22_valueChanged
     * @param arg1
     */
    void on_doubleSpinBox_22_valueChanged(double arg1);
    /**
     * @brief on_doubleSpinBox_23_valueChanged
     * @param arg1
     */
    void on_doubleSpinBox_23_valueChanged(double arg1);
    /**
     * @brief on_doubleSpinBox_31_valueChanged
     * @param arg1
     */
    void on_doubleSpinBox_31_valueChanged(double arg1);
    /**
     * @brief on_doubleSpinBox_32_valueChanged
     * @param arg1
     */
    void on_doubleSpinBox_32_valueChanged(double arg1);
    /**
     * @brief on_doubleSpinBox_33_valueChanged
     * @param arg1
     */
    void on_doubleSpinBox_33_valueChanged(double arg1);
    /**
     * @brief on_doubleSpinBox_41_valueChanged
     * @param arg1
     */
    void on_doubleSpinBox_41_valueChanged(double arg1);
    /**
     * @brief on_doubleSpinBox_42_valueChanged
     * @param arg1
     */
    void on_doubleSpinBox_42_valueChanged(double arg1);
    /**
     * @brief on_doubleSpinBox_43_valueChanged
     * @param arg1
     */
    void on_doubleSpinBox_43_valueChanged(double arg1);
    /**
     * @brief on_doubleSpinBox_44_valueChanged
     * @param arg1
     */
    void on_doubleSpinBox_44_valueChanged(double arg1);


    //////////////////////////////////////////////////
    //// Navigation
    //////////////////////////////////////////////////

    /**
     * @brief on_verticalSlider_zoom_valueChanged
     * @param value
     */
    void on_verticalSlider_zoom_valueChanged(int value);

    /**
     * @brief on_toolButton_up_clicked
     */
    void on_toolButton_up_clicked();

    /**
     * @brief on_toolButton_down_clicked
     */
    void on_toolButton_down_clicked();

    /**
     * @brief on_toolButton_left_clicked
     */
    void on_toolButton_left_clicked();

    /**
     * @brief on_toolButton_right_clicked
     */
    void on_toolButton_right_clicked();

    //////////////////////////////////////////////////
    //// Projektion
    //////////////////////////////////////////////////

    /**
     * @brief on_radioButton_orthograficPerspective_toggled
     * @param checked
     */
    void on_radioButton_orthograficPerspective_toggled(bool checked);

    /**
     * @brief on_radioButton_projectivePerspective_toggled
     * @param checked
     */
    void on_radioButton_projectivePerspective_toggled(bool checked);

    /**
     * @brief on_checkBox_stereo_toggled
     * @param checked
     */
    void on_checkBox_stereo_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QDialog *about;

    void setHomography(
            float h11, float h12, float h13,
            float h21, float h22, float h23,
            float h31, float h32, float h33,
            float h41, float h42, float h43, float h44
            );

    /**
     * @brief updateEuation
     */
    void updateEquation(void);

};

#endif // MAINWINDOW_H
