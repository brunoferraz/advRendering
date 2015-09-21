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


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    const char *loadShaderAsString(const char* file);

    GLuint prepareShader(std::string path, GLenum type);
    void readAttributes();

    GLuint programHandle;
    GLuint vaoHandle;

    void initializeGL();
    void paintGL();

signals:

public slots:
};

#endif // GLWIDGET_H
