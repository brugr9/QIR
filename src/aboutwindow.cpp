#include "aboutwindow.h"
#include "ui_aboutwindow.h"

/**
  * {@inheritDoc}
 * @brief AboutWindow::AboutWindow
 * @param parent
 */
AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
}

/**
  * {@inheritDoc}
 * @brief AboutWindow::~AboutWindow
 */
AboutWindow::~AboutWindow()
{
    delete ui;
}
