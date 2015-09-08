#ifndef __GLWIDGET__
#define __GLWIDGET__

#include <GL/glew.h>

#include <phongshader.hpp>
#include <utils/qttrackballwidget.hpp>

using namespace std;

class GLWidget : public Tucano::QtTrackballWidget
{
    Q_OBJECT

public:

    explicit GLWidget(QWidget *parent) : Tucano::QtTrackballWidget(parent) {}
    ~GLWidget() {}
    
    /**
     * @brief Initializes the shader effect
     * @todo remove hard coded mesh file!!
     */
    void initialize();

    /**
     * Repaints screen buffer.
     **/
    virtual void paintGL();

    /**
     * @brief setMeshFile
     * @param fn
     * New function to setup a meshFile var
     */
    void setMeshFile(string fn);
    /**
     * @brief setShaderDir
     * @param dir
     * New function to setup a shaderVar
     */
    void setShaderDir(string dir);


signals:
    
public slots:
    
private:

    /**
     * @brief meshFile
     * Create the two private vars to handle
     * a Mesh File and Shaders Dir
     */
    string meshFile;
    string shaderDir;
    Effects::Phong phong;
};

#endif // GLWIDGET
