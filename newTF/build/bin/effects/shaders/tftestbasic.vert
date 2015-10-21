#version 400

in vec4 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoords;
in vec4 in_Color;

out vec4 nPos;
out vec4 color;
out vec3 normal;
out vec4 vert;
out vec2 texCoords;
out float depth;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float tf;

uniform vec4 default_color;

// if attribute in_Color exists or not
uniform bool has_color;

void main(void)
{
	mat4 modelViewMatrix = viewMatrix * modelMatrix;

	mat4 normalMatrix = transpose(inverse(modelViewMatrix));
    normal = normalize(vec3(normalMatrix * vec4(in_Normal,0.0)).xyz);

	vert = modelViewMatrix * in_Position;

	depth = in_Position.z;

	texCoords = in_TexCoords;


        gl_Position = (projectionMatrix * modelViewMatrix) * in_Position;
        vec4 n = (projectionMatrix * modelViewMatrix) * in_Position;
        nPos = vec4(1.0, 0.0, 0.0, 1.0);

    if (has_color)
        color = in_Color;
    else
        color = default_color;

    if(tf == 0.0){
        color = in_Color;
    }
}