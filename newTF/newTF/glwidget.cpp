#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : Tucano::QtTrackballWidget(parent)
{

}

void GLWidget::initialize()
{
    Tucano::QtTrackballWidget::initialize();
    Tucano::QtTrackballWidget::openMesh("./models/toy.obj");
    int totalVertices =  mesh.getNumberOfVertices();
    std::vector<Eigen::Vector4f> npos;
    std::vector<Eigen::Vector4f> color;
    for(int i =0; i < totalVertices; i++)
    {
        Eigen::Vector4f v;
        v << 0, 0, 0, 1;
        npos.push_back(v);
        v << 1, 1, 0, 1;
        color.push_back(v);
    }
//    mesh.loadColors(color);
    mesh.createAttribute("nPos", npos);
//    mesh.setAttributeLocation("nPos", 3);

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
