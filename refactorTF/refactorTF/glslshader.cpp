#include "glslshader.h"

GLSLShader::GLSLShader()
{
    linked = false;
    debugStatus = true;
}

void GLSLShader::initialize()
{
    //#0 PREPARE SHADER
    GLuint vertex   = prepareShader("basic.vert", GLSL::VERTEX);
    GLuint fragment = prepareShader("basic.frag", GLSL::FRAGMENT);

    //#1 CREATE PROGRAM HANDLER
    programHandle = glCreateProgram();
    if(0 == programHandle)
    {
        logString += "Error creating program object\n";
        exit(1);
    }

    //#2 ATTACH SHADER TO PROGRAM
    glAttachShader(programHandle, fragment);
    glAttachShader(programHandle, vertex);

    //#3 & 4 LINK AND USE PROGRAM
    if(link())use();

    printActiveAttribs();
}

GLuint GLSLShader::prepareShader(const char *fileName, GLSL::GLSLShaderType type)
{
    //register shader type as String to use on log error.
    std::string wichShader;
    switch (type) {
    case GLSL::VERTEX:
        wichShader = "VERTEX";
        break;
    case GLSL::FRAGMENT:
        wichShader = "FRAGMENT";
        break;
    default:
        break;
    }

    //get shader from file;
    std::ifstream inFile( fileName );
    if(!inFile)
    {
        logString += "File < "+ std::string(fileName) + " > doesnt exist\n";
        std::cout << logString << std::endl;
        return -1;
    }
    //parse string from file
    std::stringstream code;
    code << inFile.rdbuf();
    inFile.close();
    std::string codeStr(code.str());

    //CREATE SHADER OBJ
    GLuint shaderObj = glCreateShader(type);
    if(0 == shaderObj)
    {
        logString +=  "Error creating " + wichShader + " shader";
        return -1;
    }

    //LOAD THE SOURCE CODE INTO THE SHADER OBJECT
    const GLchar* codeArray[] = {codeStr.c_str()};
    glShaderSource(shaderObj, 1, codeArray, NULL);

    //COMPILE SHADER
    glCompileShader(shaderObj);
    GLint result;
    glGetShaderiv( shaderObj, GL_COMPILE_STATUS, &result);
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
        logString += "OK - " + wichShader + " Shader Compilation Status\n" ;
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
    if(isDebug()) qDebug() << logString.c_str();
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

bool GLSLShader::isDebug()
{
    return debugStatus;
}

bool GLSLShader::isLinked()
{
    return linked;
}

