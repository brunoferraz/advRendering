#include "glslshader.h"
#include <QDebug>
GLSLShader::GLSLShader()
{
    debugStatus = false;
    m_isFirst = true;

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

/////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<Eigen::Vector4f> vdata;
    vdata.push_back(Eigen::Vector4f(-1, -1, 0, 1));
    vdata.push_back(Eigen::Vector4f(1, -1, 0, 1));
    vdata.push_back(Eigen::Vector4f(0, 1, 0, 1));

    std::vector<Eigen::Vector4f> vdataColor;
    vdataColor.push_back(Eigen::Vector4f(1, 0, 0, 1));
    vdataColor.push_back(Eigen::Vector4f(0, 1, 0, 1));
    vdataColor.push_back(Eigen::Vector4f(0, 0, 1, 1));

    createVertexAttribute(0, "in_Vertex_Position", vdata);
//    createVertexTFAttribute(0, "in_Vertex_Position", vdata);
    size = vdata.size() * 4;
    createVertexTFAttribute2("Color");
//    createVertexAttribute(1, "in_Vertex_Color", vdataColor);


//////////////////////////////////////////////////////////////////////


    //#3 LINK PROGRAM
    link();

    //#4 USE PROGRAM
    if(isLinked())use();

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

//    int size = data.size() * 4;
//    GLuint buffer;
//    glGenBuffers(1, &buffer);

//    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, buffer);
//    glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, size * sizeof(float), NULL, GL_DYNAMIC_COPY);

    size = data.size() * 4;
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

    glGenTransformFeedbacks(2, m_transformFeedback);
    glGenBuffers(2, m_particleBuffer);

    for (unsigned int i = 0; i < 2 ; i++) {
       glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[i]);
       glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[i]);
       glBufferData(GL_ARRAY_BUFFER, size, dataB, GL_DYNAMIC_DRAW);
       glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_particleBuffer[i]);
    }
}

void GLSLShader::createVertexTFAttribute2(const char *name)
{
    float colorData[] = {
        1.0f,    0.0f,    0.0f, 1.0,
        0.0f,    1.0f,    0.0f, 1.0,
        0.0f,    0.0f,    1.0f, 1.0};

     glGenBuffers(1, &m_transformFeedback[0]);

     glBindBuffer(GL_ARRAY_BUFFER, m_transformFeedback[0]);
     glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), colorData, GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);

     //glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_transformFeedback[0]);
     const char* vars[] = { name };
     glTransformFeedbackVaryings( programHandle, 1, vars, GL_INTERLEAVED_ATTRIBS );

     glBindBuffer(GL_ARRAY_BUFFER, m_transformFeedback[0]);
     glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
     glEnableVertexAttribArray(1);

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

void GLSLShader::renderTF()
{
    float positionData[] = {
        -0.8f,  -0.8f,  0.0f,
        0.8f,   -0.8f,  0.0f,
        0.0f,   0.8f,   0.0f };

//    GLuint buffer;
//    glGenBuffers(1, &buffer);
//    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, buffer);

//    GLuint id;
//    int bufferSize = 9 * sizeof(float);
//    glGenTransformFeedbacks(1, &id);
//    glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, bufferSize, NULL, GL_DYNAMIC_COPY);
//    glBindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, 0, buffer, 0, bufferSize);

//    const char* vars[] = { "in_Vertex_Position" };
//    glTransformFeedbackVaryings(programHandle, 1, vars, GL_INTERLEAVED_ATTRIBS );

//    std::vector<Eigen::Vector4f> vdata;
//    vdata.push_back(Eigen::Vector4f(-1, -1, 0, 1));
//    vdata.push_back(Eigen::Vector4f(1, -1, 0, 1));
//    vdata.push_back(Eigen::Vector4f(0, 1, 0, 1));
//    createVertexAttribute(0, "in_Vertex_Position", vdata);

//    link();
//    glBeginTransformFeedback( GL_TRIANGLES );

//    glBindVertexArray(vaoHandle);
//    glDrawArrays(GL_TRIANGLES, 0, 3);

//    std::vector<Eigen::Vector4f> feedbackData;

//    glEndTransformFeedback();
//    glFlush();
//  //  glGetBufferSubData( GL_TRANSFORM_FEEDBACK_BUFFER, 0, bufferSize, buffer  );

//    glInvalidateBufferData( buffer );
//    glDeleteTransformFeedbacks( 1, &id );
    //std::cout << "Feedback data:" << std::endl << std::endl << feedbackData << std::endl;


    //UPDATE
//    glEnable(GL_RASTERIZER_DISCARD);
//    glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[m_currVB]);
//    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[m_currTFB]);

//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, size ,(const GLvoid*)4); // position

//    glBeginTransformFeedback(GL_POINTS);

//    if (m_isFirst) {
//          glDrawArrays(GL_POINTS, 0, 1);
//          m_isFirst = false;
//      }
//      else {
//          glDrawTransformFeedback(GL_POINTS, m_transformFeedback[m_currVB]);
//      }
//    glEndTransformFeedback();
//    glDisableVertexAttribArray(0);

//    //RENDER

//    glDisable(GL_RASTERIZER_DISCARD);
//    glBindBuffer(GL_ARRAY_BUFFER, m_particleBuffer[m_currTFB]);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size, (const GLvoid*)4); // position

//    glDrawTransformFeedback(GL_POINTS, m_transformFeedback[m_currTFB]);
//    glDisableVertexAttribArray(0);

//    m_currVB = m_currTFB;
//    m_currTFB = (m_currTFB + 1) & 0x1;

//    glBindBuffer(GL_ARRAY_BUFFER, m_transformFeedback[0]);
////    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
//    glEnableVertexAttribArray(1);
//    glDisableVertexAttribArray(0);

    static float c = 0.0;

    glDisableVertexAttribArray(1);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnable(GL_RASTERIZER_DISCARD);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_transformFeedback[0]);

    GLuint location = glGetUniformLocation(programHandle, "UseTF");
    glUniform1f(location,c);
    glBindVertexArray(vaoHandle);


    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, 3);
    glEndTransformFeedback();


    glDisable(GL_RASTERIZER_DISCARD);

    glEnableVertexAttribArray(1);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);

    location = glGetUniformLocation(programHandle, "UseTF");
    glUniform1f(location, 0.0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    c += 0.01;

    if (c > 1.0) c = 0.0;

}

std::string GLSLShader::log()
{
    return logString;
}

bool GLSLShader::isDebug()
{
    return debugStatus;
}
