#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <utils/qttrackballwidget.hpp>
#include <phongshader.hpp>
#include <tfTest.hpp>
#include <mesh.hpp>

class GLWidget : public Tucano::QtTrackballWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget(){}

    void initialize();
    void paintGL();

//    Effects::Phong *phong;
    Effects::TFtest *tfTest;

};

#endif // GLWIDGET_H
