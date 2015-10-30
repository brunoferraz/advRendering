#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : Tucano::QtTrackballWidget(parent)
{
    mesh.reset();
}

void GLWidget::initialize()
{
    glViewport(0, 0, this->width(), this->height());
    Tucano::QtTrackballWidget::initialize();
    Tucano::QtTrackballWidget::openMesh("./models/toy.obj");

    int totalVert = 1000; //mesh.getNumberOfVertices();
    std::vector<Eigen::Vector4f> npos;
    std::vector<Eigen::Vector4f> vel;
    std::vector<GLuint> indices;

    for(int i = 0; i < totalVert; i++)
    {
        Eigen::Vector4f v;
        float posX = (rand() * 2 / (float)RAND_MAX);
        float posY = (rand() * 2/ (float)RAND_MAX);
        float posZ = (rand() * 2/ (float)RAND_MAX);

        v << posX, posY, posZ, 1;
//        v << 1.0, 1.0, 1.0, 1.0;
        npos.push_back(v);
        vel.push_back(v);
        indices.push_back(i);
        cout << v.transpose() << endl;
    }

//    mesh.createAttribute("nPos", npos);
//    mesh.createAttribute("nPos_2", vel);

//    mesh.setAttributeLocation("nPos_1", 3);
//    mesh.createAttribute("vel", vel);

//    mymesh.createAttribute("in_Position", npos);
    mymesh.createAttribute("inPos", npos);
//    mymesh.createAttribute("nPos2", npos);
    mymesh.loadVertices(npos);
//    mymesh.loadIndices(indices);



//    shader = new Effects::TFTest();
//    shader->setShadersDir("./effects/shaders/");
//    shader->initialize();
    simple = new Effects::SimpleTest();
    simple->setShadersDir("./effects/shaders/");
    simple->initialize();
}

void GLWidget::paintGL()
{
    makeCurrent();

    glClearColor(0.7, 0.7, 0.7, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPointSize(5);

    simple->render(mymesh, camera, light_trackball);
    camera.render();
//    update();
}
