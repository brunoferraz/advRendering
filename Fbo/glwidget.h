#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>

#include <QWidget>
#include <utils/qttrackballwidget.hpp>
#include <phongshader.hpp>
#include <effects/ssfboshader.hpp>


class GLWidget : public Tucano::QtTrackballWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initialize();
    void paintGL();
    Effects::Phong phong;
    Effects::SSFboShader fboShader;
    Mesh mesh2;

signals:

public slots:
};

#endif // GLWIDGET_H
