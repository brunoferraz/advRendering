#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <interface.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    glwidget = new GLWidget(this);
//    glwidget->resize(this->width(), this->height());
//    glwidget->initialize();
    ui->widget->initialize();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_showNormalButton_stateChanged(int arg1)
{
    Interface::showNormals = arg1;
    ui->widget->update();
}
