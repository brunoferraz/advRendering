#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <QGLWidget>
#include <fstream>
#include <string>
#include <qdebug.h>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <fstream>
using std::ifstream;
#include <sstream>
#include <string>

const char* loadShaderAsString(const char* file)
{
    std::ifstream shader_file(file, std::ifstream::in);
    std::string str((std::istreambuf_iterator<char>(shader_file)), std::istreambuf_iterator<char>());
    return str.c_str();
}
GLuint *prepareVertexShader()
{
    //#0.1 -CREATE SHADER OBJECT
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    if(vertShader==0)
    {
        std::cout << "ERROR creating Vertex shader" << std::endl;
        exit(1);
    }
    //#0.2 -COPY THE SOURCE CODE
    const GLchar * shaderCode   = loadShaderAsString("basic.vert");
    const GLchar * codeArray[]  = {shaderCode};
    glShaderSource(vertShader, 1, codeArray, NULL);
    //#0.3 -COMPILE SHADER
    glCompileShader(vertShader);
    //#0.4 -VERIFY THE COMPILATION STATUS
    GLint result;
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    if( GL_FALSE == result )
    {
        qDebug() << "FAIL - VERTEX Shader Compilation Status";
        GLint logLen;
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLen);
        if(logLen > 0)
        {
            char * log = (char *)malloc(logLen);
            GLsizei written;
            glGetShaderInfoLog(vertShader, logLen, &written, log);
            qDebug() << log;
            free(log);
        }
        return 0;
    }else{
        std::cout << "OK - VERTEX Shader Compilation Status" << std::endl;
        return &vertShader;
    }
}
GLuint *prepareFragmentShader()
{
    //#0.1 -CREATE SHADER OBJECT
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    if(fragShader==0)
    {
        std::cout << "ERROR creating Fragment shader" << std::endl;
        exit(1);
    }
    //#0.2 -COPY THE SOURCE CODE
    const GLchar * shaderCode   = loadShaderAsString("basic.frag");
    const GLchar * codeArray[]  = {shaderCode};
    glShaderSource(fragShader, 1, codeArray, NULL);
    //#0.3 -COMPILE SHADER
    glCompileShader(fragShader);
    //#0.4 -VERIFY THE COMPILATION STATUS
    GLint result;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    if( GL_FALSE == result )
    {
        qDebug() << "FAIL - FRAG Shader Compilation Status";
        GLint logLen;
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLen);
        if(logLen > 0)
        {
            char * log = (char *)malloc(logLen);
            GLsizei written;
            glGetShaderInfoLog(fragShader, logLen, &written, log);
            qDebug() << log;
            free(log);
        }
        return 0;
    }else{
        std::cout << "OK - FRAG Shader Compilation Status" << std::endl;
        return &fragShader;
    }
}
void firstTry()
{
    //#0 - PREPARE SHADER
    GLuint *fragShader      = prepareFragmentShader();
    GLuint *vertexShader    = prepareVertexShader();

    //#1 - CREATE A PROGRAM HANDLER
    GLuint programHandle = glCreateProgram();
    if(0 == programHandle)
    {
        std::cout << "Error creating program object" << std::endl;
        exit(1);
    }
    //#2 -ATTACH SHADER TO PROGRAM
    glAttachShader( programHandle, *fragShader );
    glAttachShader( programHandle, *vertexShader );

    //#3 - LINK PROGRAM
    glLinkProgram(programHandle);

    //#4 - VERIFY LINK STATUS
    GLint status;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
    if( GL_FALSE == status ){
        std::cout << "LINKING - FAILED TO LINKING SHADER PROGRAM" << std::endl;
        GLint logLen;
        glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);
        if(logLen > 0)
        {
            char *log = (char *)malloc(logLen);
            GLsizei written;
            glGetProgramInfoLog(programHandle, logLen, &written, log);
            std::cout << "PROGRAM LINK FAIL LOG | " << log << std::endl;
        }
    }else{
        std::cout << "OK - PROGRAM LINKED";
    }
    glUseProgram(programHandle);
}

void linkMe(GLint vertShader, GLint fragShader)
{
    // Create the program object
    GLuint programHandle = glCreateProgram();
    if(0 == programHandle) {
        fprintf(stderr, "Error creating program object.\n");
        exit(1);
    }

    // Bind index 0 to the shader input variable "VertexPosition"
    //glBindAttribLocation(programHandle, 0, "VertexPosition");
    // Bind index 1 to the shader input variable "VertexColor"
    //glBindAttribLocation(programHandle, 1, "VertexColor");

    // Attach the shaders to the program object
    glAttachShader( programHandle, vertShader );
    glAttachShader( programHandle, fragShader );

    // Link the program
    glLinkProgram( programHandle );

    // Check for successful linking
    GLint status;
    glGetProgramiv( programHandle, GL_LINK_STATUS, &status );
    if (GL_FALSE == status) {

        fprintf( stderr, "Failed to link shader program!\n" );

        GLint logLen;
        glGetProgramiv( programHandle, GL_INFO_LOG_LENGTH, &logLen );

        if (logLen > 0) {
            char * log = (char *)malloc(logLen);

            GLsizei written;
            glGetProgramInfoLog(programHandle, logLen, &written, log);

            fprintf(stderr, "Program log: \n%s", log);

            free(log);
        }
    } else {
        glUseProgram( programHandle );
    }
}

void initScene()
{
    //////////////////////////////////////////////////////
    /////////// Vertex shader //////////////////////////
    //////////////////////////////////////////////////////

    // Load contents of file
    std::ifstream inFile( "./basic.vert" );
    if (!inFile) {
        fprintf(stderr, "Error opening file: shader/basic.vert\n" );
        exit(1);
    }

    std::stringstream code;
    code << inFile.rdbuf();
    inFile.close();
    std::string codeStr(code.str());

    // Create the shader object
    GLuint vertShader = glCreateShader( GL_VERTEX_SHADER );
    if (0 == vertShader) {
      fprintf(stderr, "Error creating vertex shader.\n");
      exit(EXIT_FAILURE);
    }

    // Load the source code into the shader object
    const GLchar* codeArray[] = {codeStr.c_str()};
    glShaderSource(vertShader, 1, codeArray, NULL);

    // Compile the shader
    glCompileShader( vertShader );

    // Check compilation status
    GLint result;
    glGetShaderiv( vertShader, GL_COMPILE_STATUS, &result );
    if( GL_FALSE == result ) {
       fprintf( stderr, "Vertex shader compilation failed!\n" );

       GLint logLen;
       glGetShaderiv( vertShader, GL_INFO_LOG_LENGTH, &logLen );

       if (logLen > 0) {
           char * log = (char *)malloc(logLen);

           GLsizei written;
           glGetShaderInfoLog(vertShader, logLen, &written, log);

           fprintf(stderr, "Shader log: \n%s", log);

           free(log);
       }
    }

    //////////////////////////////////////////////////////
    /////////// Fragment shader //////////////////////////
    //////////////////////////////////////////////////////

    // Load contents of file into shaderCode here
    ifstream fragFile( "./basic.frag" );
    if (!fragFile) {
        fprintf(stderr, "Error opening file: shader/basic.frag\n" );
        exit(1);
    }

    std::stringstream fragCode;
    fragCode << fragFile.rdbuf();
    fragFile.close();
    codeStr = fragCode.str();

    // Create the shader object
    GLuint fragShader = glCreateShader( GL_FRAGMENT_SHADER );
    if (0 == fragShader) {
      fprintf(stderr, "Error creating fragment shader.\n");
      exit(1);
    }

    // Load the source code into the shader object
    codeArray[0] = codeStr.c_str();
    glShaderSource( fragShader, 1, codeArray, NULL );

    // Compile the shader
    glCompileShader( fragShader );

    // Check compilation status
    glGetShaderiv( fragShader, GL_COMPILE_STATUS, &result );
    if (GL_FALSE == result) {
       fprintf( stderr, "Fragment shader compilation failed!\n" );

       GLint logLen;
       glGetShaderiv( fragShader, GL_INFO_LOG_LENGTH, &logLen );

       if (logLen > 0) {
           char * log = (char *)malloc(logLen);

           GLsizei written;
           glGetShaderInfoLog(fragShader, logLen, &written, log);

           fprintf(stderr, "Shader log: \n%s", log);

           free(log);
       }
    }

    linkMe(vertShader, fragShader);

    /////////////////// Create the VBO ////////////////////
    float positionData[] = {
        -0.8f, -0.8f, 0.0f,
         0.8f, -0.8f, 0.0f,
         0.0f,  0.8f, 0.0f };
    float colorData[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f };


    // Create and populate the buffer objects
    GLuint vboHandles[2];
    GLuint vaoHandle;
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);

    // Create and set-up the vertex array object
    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray(vaoHandle);

    glEnableVertexAttribArray(0);  // Vertex position
    glEnableVertexAttribArray(1);  // Vertex color

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

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

        initScene();
    }
    return a.exec();
}
