#include "glslshader.h"
#include <QDebug>
GLSLShader::GLSLShader()
{
    debugStatus = false;
}

void GLSLShader::initialize()
{
    //#0 PREPARE SHADER
    GLuint vertexShader;
    GLuint fragmentShader;
    vertexShader    =  prepareShader("basicNew.vert", GLSL::VERTEX);
    fragmentShader  = prepareShader("basicNew.frag", GLSL::FRAGMENT);

    //#1 CREATE PROGRAM HANDLER
    programHandle = glCreateProgram();
    //programHandle = glCreateProgram();
    if(0 == programHandle)
    {
        logString +=  "Error creating program object\n";
        exit(1);
    }

    //#2 ATTACH SHADER TO PROGRAM
    glAttachShader( programHandle, fragmentShader );
    glAttachShader( programHandle, vertexShader );

    //#3 LINK PROGRAM
    link();

    //#4 USE PROGRAM
    if(isLinked())use();

    std::vector<Eigen::Vector4f> vdata;
    vdata.push_back(Eigen::Vector4f(-1, -1, 0, 1));
    vdata.push_back(Eigen::Vector4f(1, -1, 0, 1));
    vdata.push_back(Eigen::Vector4f(0, 1, 0, 1));

    std::vector<Eigen::Vector4f> vdataColor;
    vdataColor.push_back(Eigen::Vector4f(1, 0, 0, 1));
    vdataColor.push_back(Eigen::Vector4f(0, 1, 0, 1));
    vdataColor.push_back(Eigen::Vector4f(0, 0, 1, 1));

//    createVertexAttribute(0, "in_Vertex_Position", vdata);
    createVertexTFAttribute(0, "in_Vertex_Position", vdata);
    createVertexAttribute(1, "in_Vertex_Color", vdataColor);

    link();

    printActiveAttribs();
}

GLuint GLSLShader::prepareShader(const char *fileName, GLSL::GLSLShaderType type)
{
    std::string qual;
    GLenum glType;
    switch (type) {
    case GLSL::VERTEX:
        qual    = "VERTEX";
        glType  = GL_VERTEX_SHADER;
        break;
    case GLSL::FRAGMENT:
        qual    = "FRAGMENT";
        glType  = GL_FRAGMENT_SHADER;
        break;
    default:
        break;
    }
    std::ifstream inFile( fileName );
    if (!inFile) {
        logString += "File < "+ std::string(fileName) + " > doesnt exist\n";
        return -1;
    }
    std::stringstream code;
    code << inFile.rdbuf();
    inFile.close();
    std::string codeStr(code.str());

    // CREATE SHADER OBJETCT
    GLuint shaderObj = glCreateShader(glType);
    if (0 == shaderObj) {
      logString +=  "Error creating " + qual + " shader";
      exit(EXIT_FAILURE);
    }

     // LOAD THE SOURCE CODE INTO THE SHADER OBJECT
    const GLchar* codeArray[] = {codeStr.c_str()};
    glShaderSource(shaderObj, 1, codeArray, NULL);

    //COMPILE SHADER
    glCompileShader(shaderObj);
    GLint result;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &result);
    if( GL_FALSE == result )
    {
        GLint logLen;
        glGetShaderiv(shaderObj, GL_INFO_LOG_LENGTH, &logLen);
        if(logLen > 0)
        {
            char * log = (char *)malloc(logLen);
            GLsizei written;
            glGetShaderInfoLog(shaderObj, logLen, &written, log);
            logString += std::string(log) + "\n";
            free(log);
        }
        return 0;
    }else{
        logString += "OK - " + qual + " Shader Compilation Status\n" ;
        return shaderObj;
    }
}

bool GLSLShader::link()
{
    glLinkProgram(programHandle);

    //#4 VERIFY LINK STATUS
    GLint status;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
    if( GL_FALSE == status ){
        logString +=  "LINKING - FAILED TO LINKING SHADER PROGRAM\n";
        GLint logLen;
        glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);
        if(logLen > 0)
        {
            char *log = (char *)malloc(logLen);
            GLsizei written;
            glGetProgramInfoLog(programHandle, logLen, &written, log);
            logString+= "PROGRAM LINK FAIL LOG | " + std::string(log) + "\b";
        }
        return false;
    }else{
        logString+=  "OK - PROGRAM LINKED\n";
        linked = true;
        return true;
    }

}

void GLSLShader::use()
{
    glUseProgram(programHandle);
    if(isDebug()) qDebug() << log().c_str();
}

bool GLSLShader::isLinked()
{
    return linked;
}

void GLSLShader::createVertexAttribute(GLuint location, const char *name, std::vector<Eigen::Vector4f> &data)
{
    bindAttribLocation(location, name);

    int size = data.size() * 4;
    float *dataB = new float[size];
    int temp =0;
    for(int i =0; i < size; i+=4)
    {
        dataB[i] = data[temp][0];
        dataB[i+1] = data[temp][1];
        dataB[i+2] = data[temp][2];
        dataB[i+3] = data[temp][3];
        temp++;
    }


    glGenBuffers(1, &vboHandle);
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle);

    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), dataB, GL_STATIC_DRAW);

    if(vaoHandle == 0)
    {
        glGenVertexArrays(1, &vaoHandle);
    }

    glBindVertexArray(vaoHandle);
    //GLint nAttribs;
    //glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &nAttribs);
    glEnableVertexAttribArray(location);

    glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
    glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

}

void GLSLShader::createVertexTFAttribute(GLuint location, const char *name, std::vector<Eigen::Vector4f> &data)
{
//    GLuint feedback[1];

//    glGenTransformFeedbacks(1, feedback);
//    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[0]);
//    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, posBuf);
    int size = data.size() * 4;
    GLuint buffer;
    glGenBuffers(1, &buffer);

    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, buffer);
    glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, size * sizeof(float), NULL, GL_DYNAMIC_COPY);

}

void GLSLShader::bindAttribLocation(GLuint location, const char *name)
{
    glBindAttribLocation(programHandle, location, name);
}

void GLSLShader::printActiveAttribs()
{
    GLint maxLength, nAttribs;
    glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &nAttribs);
    glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

    GLchar *name = (GLchar *) malloc(maxLength);

    GLint written, size, location;
    GLenum type;
    std::printf("----------------------------------\n");
    std::printf("INDEX  | NAME\n");
    std::printf("----------------------------------\n");
    for(int i =0; i < nAttribs; i++){
        glGetActiveAttrib(programHandle, i, maxLength, &written, &size, &type, name);
        location = glGetAttribLocation(programHandle, name);
        printf(" %-5d | %s\n", location, name);
    }
    free(name);
}

void GLSLShader::render()
{
//    glEnable(GL_RASTERIZER_DISCARD);
//    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, )

    glBindVertexArray(vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

std::string GLSLShader::log()
{
    return logString;
}

bool GLSLShader::isDebug()
{
    return debugStatus;
}

