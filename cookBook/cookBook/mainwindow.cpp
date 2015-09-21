#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    glwidget = new GLWidget(this);
    glwidget->resize(this->width(), this->height());
    glwidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
