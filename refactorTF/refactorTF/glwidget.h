#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <QGLWidget>
#include <glslshader.h>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();

    GLSLShader shader;

signals:

public slots:
};

#endif // GLWIDGET_H
