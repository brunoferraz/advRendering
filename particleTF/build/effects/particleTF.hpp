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

#ifndef __PARTICLETF__
#define __PARTICLETF__

#include <tucano.hpp>
#include <camera.hpp>
#include <pointcloud.h>

using namespace Tucano;

namespace Effects
{

/**
 * @brief Renders a mesh using a Phong shader.
 */
class ParticleTF : public Effect
{

private:

    /// Phong Shader
    Shader particletf_shader;

	/// Default color
	Eigen::Vector4f default_color;

public:

    GLuint m_particleBuffer[2];
    GLuint m_transformFeedback[2];

    /**
     * @brief Default constructor.
     */
    ParticleTF (void)
    {
		default_color << 0.7, 0.7, 0.7, 1.0;
    }

    /**
     * @brief Default destructor
     */
    virtual ~ParticleTF (void) {}

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        // searches in default shader directory (/shaders) for shader files phongShader.(vert,frag,geom,comp)
        loadShader(particletf_shader, "particleTF") ;

        glGenTransformFeedbacks(2, m_transformFeedback);
        glGenBuffers(2, m_particleBuffer);

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
    void render (PointCloud& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {

        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_transformFeedback[0]);
        glBeginTransformFeedback(GL_POINTS);
        particletf_shader.bind();

        // sets all uniform variables for the phong shader
        particletf_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
        particletf_shader.setUniform("modelMatrix", mesh.getModelMatrix());
        particletf_shader.setUniform("viewMatrix", camera.getViewMatrix());
        particletf_shader.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
        particletf_shader.setUniform("has_color", mesh.hasAttribute("in_Color"));
        particletf_shader.setUniform("default_color", default_color);


        mesh.setAttributeLocation(particletf_shader);

        glEnable(GL_DEPTH_TEST);
        mesh.render();

        particletf_shader.unbind();
//        glEndTransformFeedback();
    }


};

}


#endif
