#version 150
in vec4 inPos;
in vec4 inColor;
in vec4 nColor;

out vec4 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
//      color = vec4(vec2(1.0),0.0, 1.0);
        color = inColor;
        gl_Position = projectionMatrix * modelMatrix * viewMatrix * inPos;
}
