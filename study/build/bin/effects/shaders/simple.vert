#version 400
in vec4 nPos;
in vec4 inPos;
in vec4 inColor;
//in vec4 nColor;

out vec4 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
        //vec4 ncolor = nColor;
        color = inColor;
        gl_Position = projectionMatrix * modelMatrix * viewMatrix * inPos;
}
