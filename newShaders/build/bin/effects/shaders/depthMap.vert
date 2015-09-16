#version 150

in vec4 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoords;
in vec4 in_Color;

out vec4 color;
out vec3 normal;
out vec4 vert;
out vec2 texCoords;

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

        mat4 normalMatrix = transpose(inverse(modelViewMatrix));
        normal = normalize(vec3(normalMatrix * vec4(in_Normal,0.0)).xyz);

        vert = modelViewMatrix * in_Position;

        depth = in_Position.z;

        texCoords = in_TexCoords;

//        gl_Position = (projectionMatrix * modelViewMatrix) * in_Position;
        mat4 lightModelViewMatrix = lightViewMatrix * modelMatrix;
        gl_Position = (projectionMatrix * lightModelViewMatrix) * in_Position;

    if (has_color)
        color = in_Color;
    else
        color = default_color;

    float distance = (vec4(lightViewMatrix * modelMatrix * in_Position)).z;
    distance = length((vec4((lightViewMatrix*modelMatrix) * in_Position)).xyz);
    color = vec4(distance, distance, distance, 1.0);
}
