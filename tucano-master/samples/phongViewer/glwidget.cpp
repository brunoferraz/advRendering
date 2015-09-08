#include "glwidget.hpp"
#include <QDebug>
#include <QString>

void GLWidget::initialize (void)
{
    // initialize the shader effect
    mesh.reset();
    phong.setShadersDir(shaderDir);
    phong.initialize();

    // initialize the widget, camera and light trackball, and opens default mesh
    Tucano::QtTrackballWidget::initialize();
    Tucano::QtTrackballWidget::openMesh(meshFile);
}

void GLWidget::paintGL (void)
{
    makeCurrent();

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    phong.render(mesh, camera, light_trackball);

    camera.render();
}

void GLWidget::setShaderDir(std::string dir){
    shaderDir = dir;
}

void GLWidget::setMeshFile(std::string fn){
    meshFile = fn;
}
