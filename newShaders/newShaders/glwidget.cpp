#include "glwidget.h"
#include <interface.h>

GLWidget::GLWidget(QWidget *parent) : Tucano::QtTrackballWidget(parent)
{

}

void GLWidget::initialize()
{
    Tucano::QtTrackballWidget::initialize();
    Tucano::QtTrackballWidget::openMesh("./models/toy.obj");
//    mesh.createParallelepiped(1, 1, 1);
//    mesh.createQuad();

    phong = new Effects::PhongCompleteShader();
    phong->setShadersDir("./effects/shaders/");
    phong->initialize();

    showNormals = new Effects::ShowNormals();
    showNormals->setShadersDir("./effects/shaders/");
    showNormals->initialize();

    gooch = new Effects::GoochShader();
    gooch->setShadersDir("./effects/shaders/");
    gooch->initialize();
}

void GLWidget::paintGL()
{
    makeCurrent();
    glClearColor(0.5, 0.5, 0.6, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
//    phong->render(mesh, camera, light_trackball);
    gooch->render(mesh, camera, light_trackball);

//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_FRONT);
    if(Interface::showNormals){
        showNormals->render(mesh, camera, light_trackball);
    }
    camera.render();
}
