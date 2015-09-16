#version 150

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
//        mat4 modelViewMatrix = lightViewMatrix * modelMatrix;
        lightPos = vec4(0, 0, 0, 1.0);
        lightPos = lightViewMatrix * lightPos;

        mat4 normalMatrix = transpose(inverse(modelViewMatrix));
        normal = normalize(vec3(normalMatrix * vec4(in_Normal,0.0)).xyz);

        vertLS = (projectionMatrix * lightViewMatrix * modelMatrix) * in_Position;
        vert = (projectionMatrix * modelViewMatrix) * in_Position;
        distance = normalize(vec4(lightViewMatrix * in_Position)).z;

        depth = in_Position.z;
        texCoords = in_TexCoords;
        gl_Position = vert;

        vec4 coord = vertLS;
        coord /= coord.w;
        shadowCoord = (coord +1.0) * 0.5;
//        shadowCoord = (coord * 0.5) + 1;

    if (has_color)
        color = in_Color;
    else
        color = default_color;
}
