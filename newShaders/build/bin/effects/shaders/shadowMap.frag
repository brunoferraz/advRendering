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
//      out_Color = texture(coordsTexture, vec2(gl_FragCoord.x/381,gl_FragCoord.y/281));
//       vec4 coord =  vec4(gl_FragCoord.x/381.0, gl_FragCoord.y/281.0, gl_FragCoord.z, 1.0);

//   // FUNCIONANDO COM RUIDO
    vec4 LDepth = texture2D(coordsTexture, vec2(shadowCoord.x, shadowCoord.y));
    float visibility = 1.0;
    float diff = LDepth.z - distance;
    float cosTheta = dot(normal.xyz, lightPos.xyz);
    float bias= 0.05 * tan(acos(cosTheta));

    bias = clamp(bias, 0,0.01);
    if(diff > bias){
        visibility = 0.0;
    }

    vec4 finalColor = vec4(1.0, 1.0, 1.0, 1.0) * visibility;
    finalColor.w = 1.0;

    out_Color = finalColor;

}
