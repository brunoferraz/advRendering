#version 130

in vec4 color;
in vec3 normal;
in vec4 vert;
in vec4 vertLS;
in float distance;
in vec4 shadowCoord;
in vec4 lightPos;

in vec2 texCoords;
in float depth;

out vec4 out_Color;

uniform sampler2D coordsTexture;
uniform mat4 lightViewMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
//    mat4 lightModelViewMatrix = lightViewMatrix * modelMatrix;
//    vec4 nVert = (projectionMatrix * lightModelViewMatrix) * vert;
//    float distance = length((vec4((lightViewMatrix*modelMatrix) * vert)).xyz);
//    vec4 coord = nVert;
//    coord /= coord.w;
//    coord = (coord + 1.0) * 0.5;

//    vec4 LDepth = texture2D(coordsTexture, vec2(coord.xy));
//    float diff = abs(LDepth.z - distance);
//    float cosTheta = dot(normal, lightPos.xyz);
//    float bias = 0.005 * tan(acos(cosTheta));

//    float visibility = 1.0;
//    if(diff > bias)
//    {
//        visibility = 0.0;
//    }
//    vec4 nColor = vec4(1);
//    nColor.xyz *= visibility;
//    out_Color   = nColor;

    mat4 lightModelViewMatrix = lightViewMatrix * modelMatrix;
    vec4 nVert = (projectionMatrix * lightModelViewMatrix) * vert;
    float distance = length((vec4((lightViewMatrix*modelMatrix) * vert)).xyz);
    vec4 coord = nVert;
    coord /= coord.w;
    coord = (coord + 1.0) * 0.5;

    float size = 2;

    float stepX = 1/381.0;
    float rangeX = stepX * size;
    float stepY = 1/281.0;
    float rangeY = stepY * size;

    vec4 nColor = vec4(1);
    float visibility = 1.0;
    float count = 0;
    for(float i = 0; i < rangeX; i+= stepX){
        for(float j = 0; j < rangeY; j+= stepY){
            vec4 LDepth = texture2D(coordsTexture, vec2(coord.x+ i, coord.y + j));
            float diff = abs(LDepth.z - distance);
            float cosTheta = dot(normal, lightPos.xyz);
            float bias = 0.015 * tan(acos(cosTheta));
            bias = 0.015;
            bias = clamp(bias, 0, 0.01);
            if(diff < bias)
            {
                count++;
            }
        }
    }
    visibility = count/(size * size);
    nColor.xyz *= visibility;
    out_Color   = nColor;
}
