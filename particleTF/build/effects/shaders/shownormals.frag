#version 150

in vec4 color;
in vec3 normal;

in vec2 texCoords;
in float depth;

in vec4 colorFrag;
in vec3 normalFrag;

out vec4 out_Color;

uniform mat4 lightViewMatrix;

void main(void)
{
    out_Color = vec4(0, 0, 0, 1);
}
