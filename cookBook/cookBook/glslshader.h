#ifndef GLSLSHADER_H
#define GLSLSHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <eigen3/Eigen/Eigen>


namespace GLSL {
    enum GLSLShaderType{
        VERTEX, FRAGMENT, GEOMETRY, TESS_CONTROL, TESS_EVALUATION
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

    int getHandle();
    bool isLinked();

    void createVertexAttribute(GLuint location, const char *name, std::vector<Eigen::Vector4f> &data);
    void createVertexTFAttribute(GLuint location, const char *name, std::vector<Eigen::Vector4f> &data);
    void createVertexTFAttribute2(const char *name);
    void bindAttribLocation( GLuint location, const char *name);
    void bindFragDataLocation( GLuint location, const char * name);

    void setUniform(const char *name, float x, float y, float z);
    void setUniform(const char *name, const Eigen::Vector3f &v);
    void setUniform(const char *name, const Eigen::Vector4f &v);
    void setUniform(const char *name, const Eigen::Matrix3f &m);
    void setUniform(const char *name, const Eigen::Matrix4f &m);
    void setUniform(const char *name, float val);
    void setUniform(const char *name, int val);
    void setUniform(const char *name, bool val);

    void printActiveUniforms();
    void printActiveAttribs();

    void render();
    void renderTF();

    std::string log();
private:
    GLuint          programHandle;
    GLuint          vaoHandle;
    GLuint          posBuf;
    GLuint          vboHandle;
    bool            linked;
    std::string     logString;
    bool            debugStatus;

    unsigned int m_currVB;
    unsigned int m_currTFB;
    bool  m_isFirst;
    int size;
    GLuint m_particleBuffer[2];
    GLuint m_transformFeedback[2];

    int getUniformLocation(const char *name);
    bool fileExists(const std::string & fileName);
    bool isDebug();
};

#endif // GLSLSHADER_H
