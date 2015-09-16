#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <interface.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::on_pushButton_released()
{
    if(ui->render_Phong->isChecked()) Interface::renderType = Interface::PHONG;
    if(ui->render_ShadowMap->isChecked()) Interface::renderType = Interface::SHADOWMAP;
    if(ui->render_Gooch->isChecked()) Interface::renderType = Interface::GOOCH;
    ui->widget->update();
}
