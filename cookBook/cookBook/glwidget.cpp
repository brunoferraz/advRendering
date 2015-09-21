#include "glwidget.h"


GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{

}

const char *GLWidget::loadShaderAsString(const char *file)
{
    std::ifstream shader_file(file, std::ifstream::in);
    std::string str((std::istreambuf_iterator<char>(shader_file)), std::istreambuf_iterator<char>());
    return str.c_str();
}


GLuint GLWidget::prepareShader(std::string path, GLenum type)
{
    std::string qual;
    switch (type) {
    case GL_VERTEX_SHADER:
        qual = "vertex";
        break;
    case GL_FRAGMENT_SHADER:
        qual = "fragment";
        break;
    default:
        break;
    }

    // LOAD CONTENTS OF FILE
    std::ifstream inFile( path );
    if (!inFile) {
        std::cout << "Error opening file " << path << std::endl;
        exit(1);
    }
    std::stringstream code;
    code << inFile.rdbuf();
    inFile.close();
    std::string codeStr(code.str());

    // CREATE SHADER OBJETCT
    GLuint shaderObj = glCreateShader( type );
    if (0 == shaderObj) {

      std::cout << "Error creating " << qual << " shader" << std::endl;
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
        qDebug() << "FAIL - FRAG Shader Compilation Status";
        GLint logLen;
        glGetShaderiv(shaderObj, GL_INFO_LOG_LENGTH, &logLen);
        if(logLen > 0)
        {
            char * log = (char *)malloc(logLen);
            GLsizei written;
            glGetShaderInfoLog(shaderObj, logLen, &written, log);
            qDebug() << log;
            free(log);
        }
        return 0;
    }else{
        std::cout << "OK - "<< qual <<" Shader Compilation Status" << std::endl;
    }
    return shaderObj;
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


    //#0 PREPARE SHADER
        GLuint vertexShader    = prepareShader("basic.vert", GL_VERTEX_SHADER);
        GLuint fragmentShader  = prepareShader("basic.frag", GL_FRAGMENT_SHADER);
    //#1 CREATE PROGRAM HANDLER
    programHandle = glCreateProgram();
    if(0 == programHandle)
    {
        std::cout << "Error creating program object" << std::endl;
        exit(1);
    }

    //#2 ATTACH SHADER TO PROGRAM
    glAttachShader( programHandle, fragmentShader );
    glAttachShader( programHandle, vertexShader );

    //#3 LINK PROGRAM
    glLinkProgram(programHandle);

    //#4 VERIFY LINK STATUS
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
        std::cout << "OK - PROGRAM LINKED" << std::endl;
        glUseProgram(programHandle);
    }


    //////////////////////////////////////////////////////
    /// PASS PARAMETERS INTO THE SHADERS          ////////
    /// //////////////////////////////////////////////////
    //Bind Index 0 to the shader input variable
    glBindAttribLocation(programHandle, 0, "VertexPosition");
    //Bind Index 0 to the shader input variable
    glBindAttribLocation(programHandle, 1, "VertexColor");

    //create a global variable to hold our handle to the vertex

    //POPULATE SCENE
    float positionData[] = {
        -0.8f,  -0.8f,  0.0f,
        0.8f,   -0.8f,  0.0f,
        0.0f,   0.8f,   0.0f };
    float colorData[] = {
        1.0f,    0.0f,    0.0f,
        0.0f,    1.0f,    0.0f,
        0.0f,    0.0f,    1.0f};

    //create the buffer objects
    GLuint vboHandles[2];

    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle    = vboHandles[1];


    //populate the position buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);


    //populate the color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 *sizeof(float), colorData, GL_STATIC_DRAW);

    //create and bind vertex array object, wich stores the relationship between the buffers and the input attributes
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    glEnableVertexAttribArray(0); //vertex position
    glEnableVertexAttribArray(1); //vertex color

    //map index 0 to the position buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

    //map index 1 to the color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

    readAttributes();
}

void GLWidget::readAttributes()
{
    GLint maxLength, nAttribs;
    glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &nAttribs);
    glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

    GLchar *name = (GLchar *) malloc(maxLength);

    GLint written, size, location;
    GLenum type;
    std::printf("INDEX  | NAME\n");
    std::printf("----------------------------------\n");
    for(int i =0; i < nAttribs; i++){
        glGetActiveAttrib(programHandle, i, maxLength, &written, &size, &type, name);
        location = glGetAttribLocation(programHandle, name);
        printf(" %-5d | %s\n", location, name);
    }
    free(name);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

