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
    Shader tfrender;

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

        tfTest_shader.load("tf", shaders_dir);
        const char* vars[] = {"nPos"};

        tfTest_shader.initializeTF(1, vars);
        shaders_list.push_back(&tfTest_shader);

        loadShader(tfrender, "tfrender");
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
                glDisableVertexAttribArray(tfTest_shader.getAttributeLocation("nPos"));
//                glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mesh.getAttribute("nPos")->getBufferID());
                  glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tfTest_shader.getAttributeLocation("nPos"));
                    glBeginTransformFeedback(GL_POINTS);
                        glEnable(GL_DEPTH_TEST);
                        mesh.renderPoints();
                    glEndTransformFeedback();
                glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);
                mesh.unbindBuffers();
            glDisable(GL_RASTERIZER_DISCARD);
        tfTest_shader.unbind();

        Tucano::Misc::errorCheckFunc(__FILE__, __LINE__);
    }
    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera, const Tucano::Camera& lightTrackball)
    {
//        printActiveAttribs(tfrender.getShaderProgram(), "RENDER");

        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
        tfrender.bind();
        glEnableVertexAttribArray(3);
            // sets all uniform variables for the phong shader
            tfrender.setUniform("projectionMatrix", camera.getProjectionMatrix());
            tfrender.setUniform("modelMatrix", mesh.getModelMatrix());
            tfrender.setUniform("viewMatrix", camera.getViewMatrix());
            tfrender.setUniform("lightViewMatrix", lightTrackball.getViewMatrix());
            tfrender.setUniform("has_color", mesh.hasAttribute("in_Color"));
            tfrender.setUniform("default_color", default_color);
            mesh.setAttributeLocation(tfrender);
            glEnable(GL_DEPTH_TEST);
            mesh.bindBuffers();
            mesh.renderPoints();
//            mesh.renderElements();
            mesh.unbindBuffers();
        tfrender.unbind();
    }
    void printActiveAttribs(GLuint programHandle, const char* nome)
    {
        GLint maxLength, nAttribs;
        glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &nAttribs);
        glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

        GLchar *name = (GLchar *) malloc(maxLength);

        GLint written, size, location;
        GLenum type;
        std::cout << nome << "\n" <<
                     "----------------------------------\n" <<
                     "| INDEX | NAME                   |\n" <<
                     "----------------------------------\n";
        for(int i =0; i < nAttribs; i++){
            glGetActiveAttrib(programHandle, i, maxLength, &written, &size, &type, name);
            location = glGetAttribLocation(programHandle, name);
            std::cout <<  "   " << location<< "    | " <<  name << std::endl;
        }
        std::cout << "----------------------------------\n" << std::endl;
        free(name);

    //    GLint maxLength, nAttribs;
    //    glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &nAttribs);
    //    glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

    //    GLchar *name = (GLchar *) malloc(maxLength);

    //    GLint written, size, location;
    //    GLenum type;
    //    std::printf("----------------------------------\n");
    //    std::printf("INDEX  | NAME\n");
    //    std::printf("----------------------------------\n");
    //    for(int i =0; i < nAttribs; i++){
    //        glGetActiveAttrib(programHandle, i, maxLength, &written, &size, &type, name);
    //        location = glGetAttribLocation(programHandle, name);
    //        printf(" %-5d | %s\n", location, name);
    //    }
    //    free(name);
    }


};

}


#endif
