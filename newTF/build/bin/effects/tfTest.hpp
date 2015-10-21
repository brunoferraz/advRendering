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

#ifndef __TFTEST__
#define __TFTEST__

#include <tucano.hpp>
#include <camera.hpp>
#include <QDebug>

using namespace Tucano;

namespace Effects
{

/**
 * @brief Renders a mesh using a Phong shader.
 */
class TFtest : public Effect
{

private:
    /// Phong Shader
    Shader tftest_shader;
    Shader tfrender;

    GLuint TFbuffer;

	/// Default color
	Eigen::Vector4f default_color;

public:

    /**
     * @brief Default constructor.
     */
    TFtest (void)
    {
		default_color << 0.7, 0.7, 0.7, 1.0;
    }

    /**
     * @brief Default destructor
     */
    virtual ~TFtest (void) {}

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        // searches in default shader directory (/shaders) for shader files phongShader.(vert,frag,geom,comp)

//        loadShader(tftest_shader, "tftestbasic") ;


        tftest_shader.load("tftestbasic", shaders_dir);

        const char* vars[] = { "nPos" };
        tftest_shader.initializeTF(1, vars);
        shaders_list.push_back(&tftest_shader);

        loadShader(tfrender, "tfrender");
//        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, 0);
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

        tftest_shader.bind();
            // sets all uniform variables for the phong shader
            tftest_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
            tftest_shader.setUniform("modelMatrix", mesh.getModelMatrix());
            tftest_shader.setUniform("viewMatrix", camera.getViewMatrix());
            tftest_shader.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
            tftest_shader.setUniform("has_color", mesh.hasAttribute("in_Color"));
            tftest_shader.setUniform("default_color", default_color);
//            tftest_shader.setUniform("tf", 1.0);

            mesh.setAttributeLocation(tftest_shader);
            glEnable(GL_RASTERIZER_DISCARD);
                mesh.bindBuffers();
                glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mesh.getAttribute("nPos")->getBufferID());

                glBeginTransformFeedback(GL_POINTS);
                glEnable(GL_DEPTH_TEST);
                mesh.renderPoints();

                glEndTransformFeedback();
                mesh.unbindBuffers();
            glDisable(GL_RASTERIZER_DISCARD);
        tftest_shader.unbind();
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);
//        RENDERING

        tfrender.bind();
            // sets all uniform variables for the phong shader
            tfrender.setUniform("projectionMatrix", camera.getProjectionMatrix());
            tfrender.setUniform("modelMatrix", mesh.getModelMatrix());
            tfrender.setUniform("viewMatrix", camera.getViewMatrix());
            tfrender.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
            tfrender.setUniform("has_color", mesh.hasAttribute("in_Color"));
            tfrender.setUniform("default_color", default_color);
//            tfrender.setUniform("tf", 1.0);

            mesh.setAttributeLocation(tfrender);
            mesh.bindBuffers();
            mesh.renderElements();
            mesh.unbindBuffers();
        tfrender.unbind();


    }
};

}


#endif
