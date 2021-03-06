#include "shader.h"

Shader::Shader()
{

}

void Shader::initialize()
{
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
    preparePerVertexAttributes();
}

const char *Shader::loadShaderAsString(const char *file)
{
    std::ifstream shader_file(file, std::ifstream::in);
    std::string str((std::istreambuf_iterator<char>(shader_file)), std::istreambuf_iterator<char>());
    return str.c_str();
}


GLuint Shader::prepareShader(std::string path, GLenum type)
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

void Shader::createPerVertexAttribute(const char *name, float data[])
{
    attribCounter++;
    GLuint vboHandle[1];
    glGenBuffers(1, vboHandle);
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), data, GL_STATIC_DRAW);

    if(vaoHandle == 0)
    {
        glGenVertexArrays(1, &vaoHandle);
    }

    glBindVertexArray(vaoHandle);
    //GLint nAttribs;
    //glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &nAttribs);
    glEnableVertexAttribArray(attribCounter);

    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
    glVertexAttribPointer(attribCounter, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
}



void Shader::preparePerVertexAttributes()
{
    //////////////////////////////////////////////////////
    /// PASS PARAMETERS INTO THE SHADERS          ////////
    /// //////////////////////////////////////////////////
    //Bind Index 0 to the shader input variable

    glBindAttribLocation(programHandle, 0, "VertexPosition");
    //Bind Index 0 to the shader input variable
    glBindAttribLocation(programHandle, 1, "VertexColor");
    glBindAttribLocation(programHandle, 2, "Novo");


    //create a global variable to hold our handle to the vertex

    //POPULATE SCENE
    float positionData[] = {
        -0.8f,  -0.8f,  0.0f,
        0.8f,   -0.8f,  0.0f,
        0.0f,   0.8f,   0.0f };
    float pos2Data[] = {
        -0.3f,  -0.3f,  0.0f,
        0.3f,   -0.3f,  0.0f,
        0.0f,   0.3f,   0.0f };

    float colorData[] = {
        1.0f,    0.0f,    0.0f,
        0.0f,    1.0f,    0.0f,
        0.0f,    0.0f,    1.0f};

    //create the buffer objects
//    GLuint vboHandles[2];
//    GLuint vboHandles[3];

//    glGenBuffers(2, vboHandles);
//    glGenBuffers(3, vboHandles);
//    GLuint positionBufferHandle = vboHandles[0];
//    GLuint colorBufferHandle    = vboHandles[1];
//    GLuint posNovoBufferHandle  = vboHandles[2];

//    //populate the position buffer
//    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
//    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);

//    //populate the color buffer
//    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
//    glBufferData(GL_ARRAY_BUFFER, 9 *sizeof(float), colorData, GL_STATIC_DRAW);

//    //populate the color buffer
//    glBindBuffer(GL_ARRAY_BUFFER, posNovoBufferHandle);
//    glBufferData(GL_ARRAY_BUFFER, 9 *sizeof(float), pos2Data, GL_STATIC_DRAW);

//    //create and bind vertex array object, wich stores the relationship between the buffers and the input attributes
//    glGenVertexArrays(1, &vaoHandle);
//    glBindVertexArray(vaoHandle);

//    glEnableVertexAttribArray(0); //vertex position
//    glEnableVertexAttribArray(1); //vertex color
//    glEnableVertexAttribArray(2); //vertex position


//    //map index 0 to the position buffer
//    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

//    //map index 1 to the color buffer
//    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

//    //map index 1 to the color buffer
//    glBindBuffer(GL_ARRAY_BUFFER, posNovoBufferHandle);
//    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

//    listAttributes();
      createPerVertexAttribute("VertexPosition", positionData);
      createPerVertexAttribute("VertexColor", colorData);
      createPerVertexAttribute("novo", pos2Data);

      listAttributes();
      listUniformAttributes();
}

void Shader::prepareUniformAttributes()
{
    float angle = 45;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
    GLuint location = glGetUniformLocation(programHandle, "RotationMatrix");

    glUniformMatrix4fv(location,1,GL_FALSE, &rotationMatrix[0][0]);

}

void Shader::listAttributes()
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

void Shader::listUniformAttributes()
{
    GLint nUniforms, maxLen;
    glGetProgramiv(programHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
    glGetProgramiv(programHandle, GL_ACTIVE_UNIFORMS, &nUniforms);

    GLchar *name = (GLchar *) malloc (maxLen);
    GLint size, location;
    GLsizei written;

    GLenum type;
    printf("-----------------------------------------------\n");
    printf(" Location | Name\n");
    printf("-----------------------------------------------\n");
    for( int i = 0; i < nUniforms; i++)
    {
        glGetActiveUniform(programHandle, i, maxLen, &written, &size, &type, name);
        location = glGetUniformLocation(programHandle, name);
        printf(" %-8d | %s\n ", location, name);
    }
    free(name);
}

void Shader::render()
{
    prepareUniformAttributes();

    glBindVertexArray(vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
