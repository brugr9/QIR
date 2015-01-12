#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutwindow.h"

/**
 * {@inheritDoc}
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    myGLWidget(parent)
{
    ui->setupUi(this);
}

/**
 * {@inheritDoc}
 */
MainWindow::~MainWindow()
{
    delete ui;
}


//////////////////////////////////////////////////
//// Menu
//////////////////////////////////////////////////

/**
 * {@inheritDoc}
 */
void MainWindow::on_actionMittelpunktsquadrik_triggered()
{
    this->setCoefficients(
                // a, b, c
                1.0, 1.0, 1.0,
                // f, g, h
                0.0, 0.0, 0.0,
                // p, q, r
                0.0, 0.0, 0.0,
                // d
                -1.0);
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_actionKegeliger_Typ_triggered()
{

}

/**
 * {@inheritDoc}
 */
void MainWindow::on_actionParabolischer_Typ_triggered()
{

}

/**
 * {@inheritDoc}
 */
void MainWindow::on_actionEllipsoid_triggered()
{
    this->setCoefficients(
                // a, b, c
                1.0, 1.0, 1.0,
                // f, g, h
                0.0, 0.0, 0.0,
                // p, q, r
                0.0, 0.0, 0.0,
                // d
                -1.0);
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_actionHyperboloidEinschalig_triggered()
{
    this->setCoefficients(
                // a, b, c
                1.0, -1.0, 1.0,
                // f, g, h
                0.0, 0.0, 0.0,
                // p, q, r
                0.0, 0.0, 0.0,
                // d
                -1.0);
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_actionHyperboloidZweischalig_triggered()
{
    this->setCoefficients(
                // a, b, c
                1.0, -1.0, 1.0,
                // f, g, h
                0.0, 0.0, 0.0,
                // p, q, r
                0.0, 0.0, 0.0,
                // d
                1.0);
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_actionParaboloidElliptisch_triggered()
{
    this->setCoefficients(
                // a, b, c
                1.0, 0.0, 1.0,
                // f, g, h
                0.0, 0.0, 0.0,
                // p, q, r
                0.0, -0.5, 0.0,
                // d
                0.0);
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_actionParaboloidHyperbolisch_triggered()
{
    this->setCoefficients(
                // a, b, c
                1.0, 0.0, -1.0,
                // f, g, h
                0.0, 0.0, 0.0,
                // p, q, r
                0.0, -0.5, 0.0,
                // d
                0.0);
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_actionBeenden_triggered()
{
    QApplication::quit();
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_actionInfo_triggered()
{
    about = new AboutWindow(this);
    about->show();
}

//////////////////////////////////////////////////
//// Transformation
//////////////////////////////////////////////////


/**
 * {@inheritDoc}
 */
void MainWindow::on_doubleSpinBox_11_valueChanged(double arg1)
{
    ui->myGLWidget->setH00(arg1);
    this->updateEquation();
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_doubleSpinBox_12_valueChanged(double arg1)
{
    ui->myGLWidget->setH01(arg1);
    this->updateEquation();
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_doubleSpinBox_13_valueChanged(double arg1)
{
    ui->myGLWidget->setH02(arg1);
    this->updateEquation();
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_doubleSpinBox_21_valueChanged(double arg1)
{
    ui->myGLWidget->setH10(arg1);
    this->updateEquation();
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_doubleSpinBox_22_valueChanged(double arg1)
{
    ui->myGLWidget->setH11(arg1);
    this->updateEquation();
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_doubleSpinBox_23_valueChanged(double arg1)
{
    ui->myGLWidget->setH12(arg1);
    this->updateEquation();
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_doubleSpinBox_31_valueChanged(double arg1)
{
    ui->myGLWidget->setH20(arg1);
    this->updateEquation();
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_doubleSpinBox_32_valueChanged(double arg1)
{
    ui->myGLWidget->setH21(arg1);
    this->updateEquation();
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_doubleSpinBox_33_valueChanged(double arg1)
{
    ui->myGLWidget->setH22(arg1);
    this->updateEquation();
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_doubleSpinBox_41_valueChanged(double arg1)
{
    ui->myGLWidget->setH30(arg1);
    this->updateEquation();
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_doubleSpinBox_42_valueChanged(double arg1)
{
    ui->myGLWidget->setH31(arg1);
    this->updateEquation();
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_doubleSpinBox_43_valueChanged(double arg1)
{
    ui->myGLWidget->setH32(arg1);
    this->updateEquation();
}

/**
 * {@inheritDoc}
 */
void MainWindow::on_doubleSpinBox_44_valueChanged(double arg1)
{
    ui->myGLWidget->setH33(arg1);
    this->updateEquation();
}

//////////////////////////////////////////////////
//// Navigation
//////////////////////////////////////////////////

/**
 * {@inheritDoc}
 */
void MainWindow::on_verticalSlider_zoom_valueChanged(int value)
{

}

/**
 * {@inheritDoc}
 */
void MainWindow::on_toolButton_up_clicked()
{

}

/**
 * {@inheritDoc}
 */
void MainWindow::on_toolButton_down_clicked()
{

}

/**
 * {@inheritDoc}
 */
void MainWindow::on_toolButton_left_clicked()
{

}

/**
 * {@inheritDoc}
 */
void MainWindow::on_toolButton_right_clicked()
{

}

//////////////////////////////////////////////////
//// Projektion
//////////////////////////////////////////////////


/**
 * {@inheritDoc}
 */
void MainWindow::on_radioButton_orthograficProjektion_toggled(bool checked)
{

}

/**
 * {@inheritDoc}
 */
void MainWindow::on_radioButton_projectivicProjektion_toggled(bool checked)
{

}

/**
 * {@inheritDoc}
 */
void MainWindow::on_checkBox_stereo_toggled(bool checked)
{

}

//////////////////////////////////////////////////
//// Hilfs-Methoden
//////////////////////////////////////////////////

/**
 * {@inheritDoc}
 */
void MainWindow::setCoefficients(//
        double a, double b, double c,   //
        double f, double g, double h,   //
        double p, double q, double r,   //
        double d)                       //
{

}

/**
 * {@inheritDoc}
 */
void MainWindow::updateEquation(void)
{
    /**
    QString equ;
    CQuadric *q = &ui->myGLWidget->quadric;

    if (q->getA() != 0.0f) {
        //equ.append(q->getA());
        equ.append("x<sup>2</sup>");
    }
    if (q->getB() != 0.0f) {
        //equ.append(q->getB());
        equ.append(" + y<sup>2</sup>");
    }
    if (q->getC() != 0.0f) {
        //equ.append(q->getC());
        equ.append(" + z<sup>2</sup>");
    }
    if (q->getF() != 0.0f) {
        //equ.append(q->getF() * 2);
        equ.append(" + yz");
    }
    if (q->getG() != 0.0f) {
        //equ.append(q->getG() * 2);
        equ.append(" + zx");
    }
    if (q->getH() != 0.0f) {
        //equ.append(q->getH() * 2);
        equ.append(" + xy");
    }
    if (q->getP() != 0.0f) {
        //equ.append(q->getP());
        equ.append(" + x");
    }
    if (q->getQ() != 0.0f) {
        //equ.append(q->getQ());
        equ.append(" + y");
    }
    if (q->getR() != 0.0f) {
        //equ.append(q->getR());
        equ.append(" + z");
    }
    if (q->getD() != 0.0f) {
        //equ.append(q->getD());
        equ.append(" + d");
    }
    if (equ.isEmpty() || (q->getA() == 0 & q->getB() == 0 & q->getC() == 0)) {
        equ.clear();
        equ.append("NaN");
    } else {
        equ.append(" = 0");
        if (equ.startsWith(" ")) {
            equ.remove(0,3);
        }
    }

    ui->equation->setText(equ);
    */
}
/**
 * {@inheritDoc}
 */
void MainWindow::setHomography(//
        float h11, float h12, float h13, //
        float h21, float h22, float h23, //
        float h31, float h32, float h33, //
        float h41, float h42, float h43, float h44) //
{
    ui->doubleSpinBox_11->setValue(h11);
    ui->doubleSpinBox_12->setValue(h12);
    ui->doubleSpinBox_13->setValue(h13);

    ui->doubleSpinBox_21->setValue(h21);
    ui->doubleSpinBox_22->setValue(h22);
    ui->doubleSpinBox_23->setValue(h23);

    ui->doubleSpinBox_31->setValue(h31);
    ui->doubleSpinBox_32->setValue(h32);
    ui->doubleSpinBox_33->setValue(h33);

    ui->doubleSpinBox_31->setValue(h41);
    ui->doubleSpinBox_32->setValue(h42);
    ui->doubleSpinBox_33->setValue(h43);
    ui->doubleSpinBox_33->setValue(h44);
    //
    this->updateEquation();
}
