#ifndef PHONGCOMPLETESHADER
#define PHONGCOMPLETESHADER

#include <tucano.hpp>
#include <camera.hpp>

using namespace Tucano;

namespace Effects
{

/**
 * @brief Renders a mesh using a Phong shader.
 */
class PhongCompleteShader : public Effect
{

private:

    /// Phong Shader
    Shader phong_shader;

    /// Default color
    Eigen::Vector4f default_color;

public:

    /**
     * @brief Default constructor.
     */
    PhongCompleteShader (void)
    {
        default_color << 0.7, 0.7, 0.7, 1.0;
    }

    /**
     * @brief Default destructor
     */
    virtual ~PhongCompleteShader (void) {}

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        // searches in default shader directory (/shaders) for shader files phongShader.(vert,frag,geom,comp)
        loadShader(phong_shader, "phongCompleteShader") ;
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

        phong_shader.bind();

        // sets all uniform variables for the phong shader
        phong_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
        phong_shader.setUniform("modelMatrix", mesh.getModelMatrix());
        phong_shader.setUniform("viewMatrix", camera.getViewMatrix());
        phong_shader.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
        phong_shader.setUniform("has_color", mesh.hasAttribute("in_Color"));
        phong_shader.setUniform("default_color", default_color);

        mesh.setAttributeLocation(phong_shader);

        glEnable(GL_DEPTH_TEST);
        mesh.render();

        phong_shader.unbind();
    }


};

}


#endif

