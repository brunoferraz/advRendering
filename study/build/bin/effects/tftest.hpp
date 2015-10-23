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

using namespace Tucano;

namespace Effects
{

/**
 * @brief Renders a mesh using a Phong shader.
 */
class TFTest : public Effect
{

private:

    /// Phong Shader
    Shader tfTest_shader;

	/// Default color
	Eigen::Vector4f default_color;

public:

    /**
     * @brief Default constructor.
     */
    TFTest (void)
    {
		default_color << 0.7, 0.7, 0.7, 1.0;
    }

    /**
     * @brief Default destructor
     */
    virtual ~TFTest (void) {}

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        // searches in default shader directory (/shaders) for shader files phongShader.(vert,frag,geom,comp)
        //loadShader(tfTest_shader, "phongshader") ;

        tfTest_shader.load("phongshader", shaders_dir);
        const char* vars[] = {"nPos"};

        tfTest_shader.initializeTF(1, vars);
        shaders_list.push_back(&tfTest_shader);
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
    void updateTF(Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        tfTest_shader.bind();
            mesh.setAttributeLocation(tfTest_shader);
            glEnable(GL_RASTERIZER_DISCARD);
                mesh.bindBuffers();
//                    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mesh.getAttribute("nPos")->getBufferID());
//                    glBeginTransformFeedback(GL_POINTS);
//                    glEnable(GL_DEPTH_TEST);
//                        mesh.renderPoints();
//                    glEndTransformFeedback();
//                    glBindBufferBase(GL_TRANSFORM_FEEDBACK, 0, 0);
//                mesh.unbindBuffers();
            glDisable(GL_RASTERIZER_DISCARD);
        tfTest_shader.unbind();
    }
    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
        updateTF(mesh, camera, lightTrackball);
//        Eigen::Vector4f viewport = camera.getViewport();
//        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

//        tfTest_shader.bind();

//        // sets all uniform variables for the phong shader
//        tfTest_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
//        tfTest_shader.setUniform("modelMatrix", mesh.getModelMatrix());
//        tfTest_shader.setUniform("viewMatrix", camera.getViewMatrix());
//        tfTest_shader.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
//        tfTest_shader.setUniform("has_color", mesh.hasAttribute("in_Color"));
//        tfTest_shader.setUniform("default_color", default_color);

//        mesh.setAttributeLocation(tfTest_shader);

//        glEnable(GL_DEPTH_TEST);
//        mesh.render();

//        tfTest_shader.unbind();
    }



};

}


#endif
