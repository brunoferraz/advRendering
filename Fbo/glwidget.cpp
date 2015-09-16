#include "glwidget.h"
#include <Eigen/Geometry>

GLWidget::GLWidget(QWidget *parent) : Tucano::QtTrackballWidget(parent)
{

}

void GLWidget::initialize()
{
    Tucano::QtTrackballWidget::initialize();
    Tucano::QtTrackballWidget::openMesh("./models/toy.ply");
//    mesh.createParallelepiped(1.0, 1.0, 1.0);

    phong.setShadersDir("./effects/shaders/");
    phong.initialize();

    fboShader.setShadersDir("./effects/shaders/");
    fboShader.initialize();
    mesh2.createQuad();
    Eigen::Transform<float, 3, Eigen::Affine> t;
    t = Eigen::AngleAxisf(90*3.14/180, Eigen::Vector3f(1,0,0));
    mesh2.getModelMatrix().matrix() = t.matrix();
}

void GLWidget::paintGL()
{
    makeCurrent();

    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    fboShader.render(mesh, camera, light_trackball);


    camera.render();
}

