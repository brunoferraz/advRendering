#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <stdlib.h>

GLuint theTorus;

/* Create display list with Torus and initialize state*/
const void loadShaderAsString(const char* file)
{
//   std::string str;
//   std::ifstream shaderStream(file, std::ios::in);
//   if(shaderStream.is_open())
//   {
//        std::string line = "";
//        while(getline(shaderStream, line))
//        {
//            str += "\n" + line;
//        }
//        shaderStream.close();
//        std::cout << str << std::endl;
//   }
}

void initShader()
{
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    if(vertShader == 0){
        std::cout << "error creating vertex Shader" << std::endl;
    }
//    const GLchar *shaderCode = loadShaderAsString("./novo.txt");
//    std::cout << shaderCode << std::endl;
    loadShaderAsString("novo.txt");
}

static void init(void)
{
   glShadeModel(GL_FLAT);
   glClearColor(0.0, 0.0, 0.0, 0.0);
   GLenum err = glewInit();
   if(GLEW_OK != err)
   {
       fprintf(stderr, "Error initializing GLEW: %s\n",
       glewGetErrorString(err) );
   }
   const GLubyte *renderer      = glGetString(GL_RENDERER);
   const GLubyte *vendor        = glGetString(GL_VENDOR);
   const GLubyte *glslVersion   = glGetString(GL_SHADING_LANGUAGE_VERSION);
//   const GLubyte *extensions    = glGetString(GL_EXTENSIONS);

   GLint major, minor;
   glGetIntegerv(GL_MAJOR_VERSION, &major);
   glGetIntegerv(GL_MINOR_VERSION, &minor);

   std::cout << renderer << std::endl;
   std::cout << vendor << std::endl;
   std::cout << glslVersion << std::endl;
//   std::cout << major << std::endl;
//   std::cout << minor << std::endl;
//   std::cout << extensions << std::endl;

//   GLint nExtensions;
//   glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
//   for( int i = 0; i < nExtensions; i++ )
//   printf("%s\n", glGetStringi( GL_EXTENSIONS, i ) );

   initShader();

}


void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glCallList(theTorus);
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(30, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

/* Rotate about x-axis when "x" typed; rotate about y-axis
   when "y" typed; "i" returns torus to original view */
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   case 'x':
   case 'X':
      glRotatef(30.,1.0,0.0,0.0);
      glutPostRedisplay();
      break;
   case 'y':
   case 'Y':
      glRotatef(30.,0.0,1.0,0.0);
      glutPostRedisplay();
      break;
   case 'i':
   case 'I':
      glLoadIdentity();
      gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
      glutPostRedisplay();
      break;
   case 27:
      exit(0);
      break;
   }
}

int main(int argc, char **argv)
{
   glutInitWindowSize(200, 200);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
