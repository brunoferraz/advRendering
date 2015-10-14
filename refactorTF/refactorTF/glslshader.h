#ifndef GLSLSHADER_H
#define GLSLSHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <eigen3/Eigen/Eigen>
#include <QDebug>

namespace GLSL {
    enum GLSLShaderType{
        VERTEX          = GL_VERTEX_SHADER,
        FRAGMENT        = GL_FRAGMENT_SHADER,
        GEOMETRY        = GL_GEOMETRY_SHADER,
        TESS_CONTROL    = GL_TESS_CONTROL_SHADER,
        TESS_EVALUATION = GL_TESS_EVALUATION_SHADER
    };
}

class GLSLShader
{
public:
    GLSLShader();

    void initialize();
    GLuint prepareShader(const char * fileName, GLSL::GLSLShaderType type);

    bool link();
    void use();

    void createVertexAttribute(GLuint location, const char *name, std::vector<Eigen::Vector4f> &data);
    void createVertexAttributeTF(const char *name, std::vector<Eigen::Vector4f> &data);
    void bindAttribLocation( GLuint location, const char *name);
    void setUniform(const char *name, float val);

    void printActiveUniforms();
    void printActiveAttribs();

    void render();
    void renderTF();

private:
    GLuint programHandle;
    GLuint vaoHandle;

    GLuint TFbuffer;

    std::string logString;
    bool fileExists(const std::string & fileName);
    bool isDebug();
    bool isLinked();

    bool linked;
    bool debugStatus;

};

#endif // GLSLSHADER_H
