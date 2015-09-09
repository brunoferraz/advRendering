#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <utils/qttrackballwidget.hpp>

#include <phongshader.hpp>
#include <phongcompleteshader.h>
#include <shownormals.h>
#include <goochshader.h>


class GLWidget : public Tucano::QtTrackballWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initialize();
    void paintGL();

signals:

private:
    Effects::ShowNormals *showNormals;

    Effects::PhongCompleteShader *phong;
    Effects::GoochShader *gooch;

public slots:
};

#endif // GLWIDGET_H