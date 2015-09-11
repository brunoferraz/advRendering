#ifndef SHOWNORMALS
#define SHOWNORMALS

#include <tucano.hpp>
#include <camera.hpp>

using namespace Tucano;

namespace Effects {

class ShowNormals : public Effect
{
private:
    Shader showNormals_shader;
    Eigen::Vector4f default_color;

public:
    ShowNormals(void)
    {
        default_color << 0.7, 0.7, 0.7, 1.0;
    }

    ~ShowNormals(void){}

    void initialize(void)
    {
        loadShader(showNormals_shader, "shownormals");
    }

    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {

        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        showNormals_shader.bind();

        // sets all uniform variables for the phong shader
        showNormals_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
        showNormals_shader.setUniform("modelMatrix", mesh.getModelMatrix());
        showNormals_shader.setUniform("viewMatrix", camera.getViewMatrix());
        showNormals_shader.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
        showNormals_shader.setUniform("has_color", mesh.hasAttribute("in_Color"));
        showNormals_shader.setUniform("default_color", default_color);

        mesh.setAttributeLocation(showNormals_shader);

        glEnable(GL_DEPTH_TEST);
        mesh.render();

        showNormals_shader.unbind();
    }
};

}

#endif // SHOWNORMALS

