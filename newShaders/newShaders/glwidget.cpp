#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : Tucano::QtTrackballWidget(parent)
{

}

void GLWidget::initialize()
{
    Tucano::QtTrackballWidget::initialize();
    Tucano::QtTrackballWidget::openMesh("./models/toy.obj");
//    mesh.createParallelepiped(1, 1, 1);

    phong = new Effects::PhongCompleteShader();
    phong->setShadersDir("./effects/shaders/");
    phong->initialize();

    showNormals = new Effects::ShowNormals();
    showNormals->setShadersDir("./effects/shaders/");
    showNormals->initialize();
}

void GLWidget::paintGL()
{
    makeCurrent();
    glClearColor(0.5, 0.5, 0.6, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    phong->render(mesh, camera, light_trackball);
    showNormals->render(mesh, camera, light_trackball);
    camera.render();
}
