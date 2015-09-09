#ifndef GOOCHSHADER
#define GOOCHSHADER


#include <tucano.hpp>
#include <camera.hpp>

using namespace Tucano;

namespace Effects
{

/**
 * @brief Renders a mesh using a Phong shader.
 */
class GoochShader : public Effect
{

private:

    /// Phong Shader
    Shader gooch_shader;

    /// Default color
    Eigen::Vector4f default_color;

public:

    /**
     * @brief Default constructor.
     */
    GoochShader (void)
    {
        default_color << 0.7, 0.7, 0.7, 1.0;
    }

    /**
     * @brief Default destructor
     */
    virtual ~GoochShader (void) {}

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        // searches in default shader directory (/shaders) for shader files phongShader.(vert,frag,geom,comp)
        loadShader(gooch_shader, "gooch") ;
    }

    /**
    * @brief Sets the default color, usually used for meshes without color attribute
    */
    void setDefaultColor ( Eigen::Vector4f& color )
    {
        default_color = color;
    }

    /** * @brief Render the mesh given a camera and light, using a Phong shader
     * @param mesh Given mesh
     * @param camera Given camera
     * @param lightTrackball Given light camera
     */
    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {

        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        gooch_shader.bind();

        // sets all uniform variables for the phong shader
        gooch_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
        gooch_shader.setUniform("modelMatrix", mesh.getModelMatrix());
        gooch_shader.setUniform("viewMatrix", camera.getViewMatrix());
        gooch_shader.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
        gooch_shader.setUniform("has_color", mesh.hasAttribute("in_Color"));
        gooch_shader.setUniform("default_color", default_color);

        mesh.setAttributeLocation(gooch_shader);

        glEnable(GL_DEPTH_TEST);
        mesh.render();

        gooch_shader.unbind();
    }


};

}


#endif // GOOCHSHADER

