#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <utils/qttrackballwidget.hpp>
#include <phongshader.hpp>
#include <tftest.hpp>
#include <simpleTest.hpp>
#include <simpleTF.hpp>

class GLWidget : public Tucano::QtTrackballWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initialize();
    void paintGL();

    Effects::TFTest *shader;
    Effects::SimpleTest *simple;
    Effects::SimpleTF *simpleTF;

    Mesh mymesh;

signals:

public slots:
};

#endif // GLWIDGET_H
