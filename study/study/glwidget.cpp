#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : Tucano::QtTrackballWidget(parent)
{

}

void GLWidget::initialize()
{
    glViewport(0, 0, this->width(), this->height());
    Tucano::QtTrackballWidget::initialize();
    Tucano::QtTrackballWidget::openMesh("./models/toy.obj");

    int totalVert = mesh.getNumberOfVertices();
    std::vector<Eigen::Vector4f> npos;
    std::vector<Eigen::Vector4f> vel;
    for(int i = 0; i < totalVert; i++)
    {
        Eigen::Vector4f v;
        v << 0, 0, 0, 1;
        npos.push_back(v);
        vel.push_back(v);
    }
    mesh.createAttribute("nPos", npos);
    mesh.setAttributeLocation("nPos", 3);
    mesh.createAttribute("vel", vel);

    shader = new Effects::TFTest();
    shader->setShadersDir("./effects/shaders/");
    shader->initialize();

}

void GLWidget::paintGL()
{
    makeCurrent();

    glClearColor(0.7, 0.7, 0.7, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    shader->render(mesh, camera, light_trackball);
    camera.render();
    update();
}
