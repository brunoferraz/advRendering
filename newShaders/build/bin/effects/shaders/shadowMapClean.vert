#version 130

in vec4 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoords;
in vec4 in_Color;

out vec4 color;
out vec3 normal;
out vec4 vert;
out vec2 texCoords;
out vec4 vertLS;
out float distance;
out vec4 shadowCoord;
out vec4 lightPos;

out float depth;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 lightViewMatrix;

uniform vec4 default_color;

// if attribute in_Color exists or not
uniform bool has_color;

void main(void)
{
    mat4 modelViewMatrix = viewMatrix * modelMatrix;
    mat4 lightModelViewMatrix = lightViewMatrix * modelMatrix;

    texCoords = in_TexCoords;

    vert = in_Position;

    vertLS = (projectionMatrix * lightModelViewMatrix) * in_Position;
    gl_Position = (projectionMatrix * modelViewMatrix) * in_Position;
//    gl_Position = vertLS;

    distance = normalize(vec4(lightViewMatrix * in_Position)).z;

    shadowCoord = vertLS / vertLS.w;
    shadowCoord= (shadowCoord + 1.0) * 0.5;

    if (has_color)
        color = in_Color;
    else
        color = default_color;
}
