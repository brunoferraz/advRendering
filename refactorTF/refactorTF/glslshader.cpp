#include "glslshader.h"

GLSLShader::GLSLShader()
{
    linked = false;
    debugStatus = true;
}

void GLSLShader::initializeTF()
{
    GLuint vertex   = prepareShader("basic.vert", GLSL::VERTEX);
    firstProgram = glCreateProgram();
    programHandle = &firstProgram;
    if(0 == *programHandle)
    {
        logString += "Error creating program object\n";
        exit(1);
    }
    glAttachShader(*programHandle, vertex);
    if(link())use();
}

void GLSLShader::initialize()
{
    //#0 PREPARE SHADER
    GLuint vertex   = prepareShader("basic.vert", GLSL::VERTEX);
    GLuint fragment = prepareShader("basic.frag", GLSL::FRAGMENT);

    //#1 CREATE PROGRAM HANDLER
    secondProgram = glCreateProgram();
    programHandle = &secondProgram;
    if(0 == *programHandle)
    {
        logString += "Error creating program object\n";
        exit(1);
    }

    //#2 ATTACH SHADER TO PROGRAM
    glAttachShader(*programHandle, fragment);
    glAttachShader(*programHandle, vertex);

    //#3 & 4 LINK AND USE PROGRAM
    if(link())use();

    std::vector<Eigen::Vector4f> vdata;
    vdata.push_back(Eigen::Vector4f(-1, -1, 0, 1));
    vdata.push_back(Eigen::Vector4f(1, -1, 0, 1));
    vdata.push_back(Eigen::Vector4f(0, 1, 0, 1));

    std::vector<Eigen::Vector4f> vdataColor;
    vdataColor.push_back(Eigen::Vector4f(1, 0, 0, 1));
    vdataColor.push_back(Eigen::Vector4f(0, 1, 0, 1));
    vdataColor.push_back(Eigen::Vector4f(0, 0, 1, 1));

    createVertexAttribute(0, "in_Position", vdata);
    createVertexAttribute(1, "in_Color", vdataColor);
    createVertexAttributeTF("Color", vdataColor);
    printActiveAttribs();

    //#3 & 4 LINK AND USE PROGRAM
    if(link())use();
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
    glLinkProgram(*programHandle);

    //#4 VERIFY LINK STATUS
    GLint status;
    glGetProgramiv(*programHandle, GL_LINK_STATUS, &status);
    if( GL_FALSE == status ){
        logString +=  "LINKING - FAILED TO LINKING SHADER PROGRAM\n";
        GLint logLen;
        glGetProgramiv(*programHandle, GL_INFO_LOG_LENGTH, &logLen);
        if(logLen > 0)
        {
            char *log = (char *)malloc(logLen);
            GLsizei written;
            glGetProgramInfoLog(*programHandle, logLen, &written, log);
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
    glUseProgram(*programHandle);
    if(isDebug()) qDebug() << logString.c_str();
}

void GLSLShader::createVertexAttribute(GLuint location, const char *name, std::vector<Eigen::Vector4f> &data)
{
    bindAttribLocation(location, name);

    int size = data.size() * 4;
    float *dataB = new float[size];
    int temp = 0;
    for(int i = 0; i < size; i+=4)
    {
        dataB[i]    = data[temp][0];
        dataB[i+1]  = data[temp][1];
        dataB[i+2]  = data[temp][2];
        dataB[i+3]  = data[temp][3];
        temp++;
    }
    GLuint vboHandle;
    glGenBuffers(1, &vboHandle);
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle);

    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), dataB, GL_STATIC_DRAW);

    if(vaoHandle == 0)
    {
        glGenVertexArrays(1, &vaoHandle);
    }
    glBindVertexArray(vaoHandle);
    glEnableVertexAttribArray(location);

    glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
    glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
}

void GLSLShader::createVertexAttributeTF(const char *name, std::vector<Eigen::Vector4f> &data)
{

    glGenBuffers(1, &TFbuffer);

    glBindBuffer(GL_ARRAY_BUFFER, TFbuffer);
    glBufferData(GL_ARRAY_BUFFER, data.size() * 4 * sizeof(GLfloat), 0, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    const char* vars[] = { name };
    glTransformFeedbackVaryings(*programHandle, 1, vars, GL_INTERLEAVED_ATTRIBS);
    glBindBuffer(GL_ARRAY_BUFFER, TFbuffer);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
//    glEnableVertexAttribArray(0);
}

void GLSLShader::bindAttribLocation(GLuint location, const char *name)
{
    glBindAttribLocation(*programHandle, location, name);
}

void GLSLShader::setUniform(const char *name, float val)
{
    GLuint location = glGetUniformLocation(*programHandle, name);
    glUniform1f(location, val);
}

void GLSLShader::printActiveAttribs()
{
    GLint maxLength, nAttribs;
    glGetProgramiv(*programHandle, GL_ACTIVE_ATTRIBUTES, &nAttribs);
    glGetProgramiv(*programHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

    GLchar *name = (GLchar *) malloc(maxLength);

    GLint written, size, location;
    GLenum type;
    std::cout << "----------------------------------\n" <<
                 "| INDEX | NAME                   |\n" <<
                 "----------------------------------\n";
    for(int i =0; i < nAttribs; i++){
        glGetActiveAttrib(*programHandle, i, maxLength, &written, &size, &type, name);
        location = glGetAttribLocation(*programHandle, name);
        std::cout <<  "   " << location<< "    | " <<  name << std::endl;
    }
    std::cout << "----------------------------------\n" << std::endl;
    free(name);

//    GLint maxLength, nAttribs;
//    glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &nAttribs);
//    glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

//    GLchar *name = (GLchar *) malloc(maxLength);

//    GLint written, size, location;
//    GLenum type;
//    std::printf("----------------------------------\n");
//    std::printf("INDEX  | NAME\n");
//    std::printf("----------------------------------\n");
//    for(int i =0; i < nAttribs; i++){
//        glGetActiveAttrib(programHandle, i, maxLength, &written, &size, &type, name);
//        location = glGetAttribLocation(programHandle, name);
//        printf(" %-5d | %s\n", location, name);
//    }
//    free(name);
}

void GLSLShader::render()
{
    glBindVertexArray(vaoHandle);
    static float c = 0.01;
    setUniform("factor", c);
    c+= 0.01;

    glDrawArrays(GL_TRIANGLES,0,3);
}

void GLSLShader::renderTF()
{
    glDisableVertexAttribArray(1);
    glEnable(GL_RASTERIZER_DISCARD);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, TFbuffer);
        setUniform("factor", 1.0);

        glBindVertexArray(vaoHandle);

        glBeginTransformFeedback(GL_POINTS);
        glDrawArrays(GL_POINTS, 0, 3);
        glEndTransformFeedback();

     glDisable(GL_RASTERIZER_DISCARD);

     glEnableVertexAttribArray(1);
     glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);

     glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLuint *GLSLShader::getProgramHandle() const
{
    return programHandle;
}

void GLSLShader::setProgramHandle(GLuint *value)
{
    programHandle = value;
}

bool GLSLShader::isDebug()
{
    return debugStatus;
}

bool GLSLShader::isLinked()
{
    return linked;
}

