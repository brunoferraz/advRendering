#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : Tucano::QtTrackballWidget(parent)
{

}

void GLWidget::initialize()
{
    Tucano::QtTrackballWidget::initialize();
    Tucano::QtTrackballWidget::openMesh("./models/toy.obj");

    tfTest = new Effects::TFtest();
    tfTest->setShadersDir("./effects/shaders/");
    tfTest->initialize();
}

void GLWidget::paintGL()
{
    makeCurrent();

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    tfTest->render(mesh, camera, light_trackball);
    camera.render();
}
