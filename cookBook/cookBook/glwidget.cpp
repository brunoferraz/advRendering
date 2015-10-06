#include "glwidget.h"


GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{

}



void GLWidget::initializeGL()
{
    glViewport(0, 0, this->width(), this->height());
    QGLWidget::initializeGL();

    //GLEW - INIT AND TEST
    GLenum err = glewInit();
    if(GLEW_OK != err){
        std::cout << glewGetErrorString(err) << std::endl;
    }else{
        std::cout << "GLEW OK" << std::endl;
        const GLubyte *renderer = glGetString(GL_RENDERER);
        const GLubyte *vendor   = glGetString(GL_VENDOR);
        const GLubyte *version  = glGetString(GL_VERSION);
        const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

        std::cout << renderer << " | " << vendor << std::endl;
        std::cout << "OPENGL  |  version: " << version << std::endl;
        std::cout << "GLSL    |  version: " << glslVersion << std::endl;
     }
    program.initialize();
//    shader.initialize();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
//    shader.render();
    program.render();
}

