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
    std::vector<Eigen::Vector4f> inColor;
    std::vector<Eigen::Vector4f> nColor;
    std::vector<Eigen::Vector4f> vColor;

    std::vector<GLuint> indices;

    for(int i = 0; i < totalVert; i++)
    {
        Eigen::Vector4f v;
        Eigen::Vector4f c;
        Eigen::Vector4f b;
        float posX = (rand() * 2/ (float)RAND_MAX);
        float posY = (rand() * 2/ (float)RAND_MAX);
        float posZ = (rand() * 2/ (float)RAND_MAX);

        v << posX, posY, posZ, 1;
        c << 1.0, 0.0, 0.0, 1.0;
        inColor.push_back(c);
        npos.push_back(v);
        b << 0.0, 0.0, 1.0, 1.0;
        nColor.push_back(b);
        vColor.push_back(v);
    }

    mymesh.createAttribute("positions1", npos);
    mymesh.createAttribute("positions2", npos);
    mymesh.createAttribute("inColor", vColor);
    mymesh.createAttribute("nColor", nColor);
    mymesh.createAttribute("vColor", vColor);
    mymesh.loadVertices(npos);


//    simple = new Effects::SimpleTest();
//    simple->setShadersDir("./effects/shaders/");
//    simple->initialize();

//    simpleTF = new Effects::SimpleTF();
//    simpleTF->setShadersDir("./effects/shaders/");
//    simpleTF->initialize();

    pingpong = new Effects::PingPong();
    pingpong->setShadersDir("./effects/shaders/");
    pingpong->initialize();

//    shader = new Effects::TFTest();
//    shader->setShadersDir("./effects/shaders/");
//    shader->initialize();
}

void GLWidget::paintGL()
{
    makeCurrent();

    glClearColor(0.7, 0.7, 0.7, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPointSize(2);

//    simple->render(mymesh, camera, light_trackball);
//    simpleTF->render(mymesh, camera, light_trackball);
//    shader->render(mymesh, camera, light_trackball);
    pingpong->render(mymesh, camera, light_trackball);

    camera.render();
    update();
}
