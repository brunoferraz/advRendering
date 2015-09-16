/**
 * Tucano - A library for rapid prototying with Modern OpenGL and GLSL
 * Copyright (C) 2014
 * LCG - Laboratório de Computação Gráfica (Computer Graphics Lab) - COPPE
 * UFRJ - Federal University of Rio de Janeiro
 *
 * This file is part of Tucano Library.
 *
 * Tucano Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tucano Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tucano Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SSFBO_SHADER__
#define __SSFBO_SHADER__

#include <tucano.hpp>
#include <camera.hpp>

using namespace Tucano;

namespace Effects
{

/**
 * @brief Renders a mesh using a Phong shader.
 */
class SSFboShader : public Effect
{

private:

    ///FBO
    Framebuffer *fbo;

    /// SSFBO Shader
    Shader ssfbo_shader;
    Shader depthMap;
    Shader shadowMap;

	/// Default color
	Eigen::Vector4f default_color;

    int depthTextureID;
    int shadowMapTextureID;
    int normalTextureID;

    Mesh quad;
public:

    /**
     * @brief Default constructor.
     */
    SSFboShader (void)
    {
		default_color << 0.7, 0.7, 0.7, 1.0;
        depthTextureID      = 0;
        shadowMapTextureID  = 1;
        normalTextureID     = 2;
        fbo = 0;
    }

    /**
     * @brief Default destructor
     */
    virtual ~SSFboShader (void) {
        delete fbo;
    }

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        // searches in default shader directory (/shaders) for shader files phongShader.(vert,frag,geom,comp)
        loadShader(depthMap,     "depthMap");
        loadShader(ssfbo_shader, "ssfboshader");
        loadShader(shadowMap,    "shadowMapClean");

        fbo = new Framebuffer();
        quad.createQuad();
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
        Eigen::Vector2i viewport_size = camera.getViewportSize();
        int size = 4;
        viewport << 0, 0, 381 *size, 281 *size;
        viewport_size << viewport[2], viewport[3];
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
//        std::cout << viewport_size.transpose() << std::endl;
        // check if viewport was modified, if so, regenerate fbo
        if (fbo->getWidth() != viewport_size[0] || fbo->getHeight() != viewport_size[1])
        {
          fbo->create(viewport_size[0], viewport_size[1], 1);
        }

         getFboDepthMap(mesh, camera, lightTrackball);
         computeShadowMap(mesh, camera, lightTrackball);
//        getRenderDepthMap(mesh, camera, lightTrackball);
//        renderFinal(mesh, camera, lightTrackball);
    }
    void getFboDepthMap (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        fbo->clearAttachments();
        fbo->bindRenderBuffer(depthTextureID);

        depthMap.bind();

        // sets all uniform variables for the phong shader
        depthMap.setUniform("projectionMatrix",     camera.getProjectionMatrix());
        depthMap.setUniform("modelMatrix",          mesh.getModelMatrix());
        depthMap.setUniform("viewMatrix",           camera.getViewMatrix());
        depthMap.setUniform("lightViewMatrix",      lightTrackball.getViewMatrix());
        depthMap.setUniform("has_color",            mesh.hasAttribute("in_Color"));
        depthMap.setUniform("default_color",        default_color);

        mesh.setAttributeLocation(depthMap);


        glEnable(GL_DEPTH_TEST);

        mesh.render();

        depthMap.unbind();
        fbo->unbind();
        fbo->clearDepth();
    }

    void getRenderDepthMap (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        depthMap.bind();

        // sets all uniform variables for the phong shader
        depthMap.setUniform("projectionMatrix", camera.getProjectionMatrix());
        depthMap.setUniform("modelMatrix", mesh.getModelMatrix());
        depthMap.setUniform("viewMatrix", camera.getViewMatrix());
        depthMap.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
        depthMap.setUniform("has_color", mesh.hasAttribute("in_Color"));
        depthMap.setUniform("default_color", default_color);

        mesh.setAttributeLocation(depthMap);

        glEnable(GL_DEPTH_TEST);
        mesh.render();

        depthMap.unbind();
    }
    void computeShadowMap(Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
        //std::cout << viewport.transpose() << std::endl;
        //fbo->bindRenderBuffer(shadowMapTextureID);

        shadowMap.bind();

//        Texture t = fbo->getTexture(depthTextureID);

        shadowMap.setUniform("coordsTexture", fbo->bindAttachment(depthTextureID));
        // sets all uniform variables for the phong shader
        shadowMap.setUniform("projectionMatrix", camera.getProjectionMatrix());
        shadowMap.setUniform("modelMatrix", mesh.getModelMatrix());
        shadowMap.setUniform("viewMatrix", camera.getViewMatrix());
        shadowMap.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
        shadowMap.setUniform("has_color", mesh.hasAttribute("in_Color"));
        shadowMap.setUniform("default_color", default_color);

        mesh.setAttributeLocation(shadowMap);

//        quad.setAttributeLocation(shadowMap);
        glEnable(GL_DEPTH_TEST);
        mesh.render();
//        quad.render();
        fbo->unbind();
        shadowMap.unbind();
    }
    void renderFinal (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        ssfbo_shader.bind();

        // sets all uniform variables for the phong shader
        ssfbo_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
        ssfbo_shader.setUniform("modelMatrix", mesh.getModelMatrix());
        ssfbo_shader.setUniform("viewMatrix", camera.getViewMatrix());
        ssfbo_shader.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
        ssfbo_shader.setUniform("has_color", mesh.hasAttribute("in_Color"));
        ssfbo_shader.setUniform("default_color", default_color);

        mesh.setAttributeLocation(ssfbo_shader);

        glEnable(GL_DEPTH_TEST);
        mesh.render();

        ssfbo_shader.unbind();
    }
};
}


#endif
