#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <QGLWidget>
#include <QDebug>
#include <shader.h>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    Shader shader;

    void initializeGL();
    void paintGL();

signals:

public slots:
};

#endif // GLWIDGET_H
