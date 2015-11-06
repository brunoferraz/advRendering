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

#ifndef __PINGPONG__
#define __PINGPONG__

#include <tucano.hpp>
#include <camera.hpp>

using namespace Tucano;

namespace Effects
{

/**
 * @brief Renders a mesh using a Phong shader.
 */
class PingPong : public Effect
{

private:

    /// Phong Shader
    Shader pprender;
    Shader pptf;

    VertexAttribute *write_va;
    VertexAttribute *read_va;

	/// Default color
	Eigen::Vector4f default_color;

public:

    /**
     * @brief Default constructor.
     */
    PingPong (void)
    {
		default_color << 0.7, 0.7, 0.7, 1.0;
        read_va = NULL;
        write_va = NULL;
    }

    /**
     * @brief Default destructor
     */
    virtual ~PingPong (void) {}

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        // searches in default shader directory (/shaders) for shader files phongShader.(vert,frag,geom,comp)
        loadShader(pprender, "pptfrender") ;
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

        pprender.bind();

        // sets all uniform variables for the phong shader
        pprender.setUniform("projectionMatrix", camera.getProjectionMatrix());
        pprender.setUniform("modelMatrix", mesh.getModelMatrix());
        pprender.setUniform("viewMatrix", camera.getViewMatrix());
        pprender.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
        pprender.setUniform("has_color", mesh.hasAttribute("in_Color"));
        pprender.setUniform("default_color", default_color);

        if(read_va == NULL){
            read_va = mesh.getAttribute("positions1");
            write_va = mesh.getAttribute("positions2");
        }
        read_va->enable(pprender.getAttributeLocation("in_Position"));
        mesh.getAttribute("inColor")->enable(pprender.getAttributeLocation("in_Color"));

        glEnable(GL_DEPTH_TEST);
        mesh.render();

        pprender.unbind();
    }
};

}


#endif
