#version 150

in vec4 color;
in vec3 normal;
in vec4 vert;

in vec2 texCoords;
in float depth;

out vec4 out_Color;

uniform mat4 lightViewMatrix;
uniform sampler2D ParticleTex;

//layout (location = 0) out vec4 FragColor;

void main(void)
{
//    FragColor = texture2D(ParticleTex, gl_PointCoord);
    out_Color = texture2D(ParticleTex, gl_PointCoord);
}
