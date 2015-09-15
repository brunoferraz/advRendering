#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : Tucano::QtTrackballWidget(parent)
{
     timer = new QTimer(this);
     connect(timer,SIGNAL(timeout()), this, SLOT(loop()));
     timer->start(10);
}

void GLWidget::initialize()
{
    Tucano::QtTrackballWidget::initialize();
    Tucano::QtTrackballWidget::openMesh("./models/toy.obj");
//    mesh.createParallelepiped(1, 1, 1);
//    mesh.createQuad();

//    phong = new Effects::Phong();
//    phong->setShadersDir("./effects/shaders/");
//    phong->initialize();

    particleShader = new Effects::ParticleTF();
    particleShader->setShadersDir("./effects/shaders/");
    particleShader->initialize();
}

void GLWidget::paintGL()
{
    makeCurrent();
    glClearColor(0.5, 0.5, 0.6, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glPointSize(2);
    particleShader->render(pointCloud, camera, light_trackball);

    camera.render();
}

void GLWidget::loop()
{
    emitter.update();
    pointCloud.loadParticles(emitter);
    update();
}
