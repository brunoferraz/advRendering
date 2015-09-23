#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QDebug>
#include <array>
#include <vector>
#include <Eigen/Eigen>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Shader
{
public:
    Shader();

    const char *loadShaderAsString(const char* file);
    GLuint programHandle;
    GLuint vaoHandle;
    int attribCounter = -1;

    void initialize();

    GLuint prepareShader(std::string path, GLenum type);

    void createPerVertexAttribute(const char * name, float data[]);
    void preparePerVertexAttributes();
    void prepareUniformAttributes();

    void listAttributes();
    void listUniformAttributes();
    void render();
};

#endif // SHADER_H
