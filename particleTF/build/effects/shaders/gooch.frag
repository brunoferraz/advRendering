#version 150

in vec4 color;
in vec3 normal;
in vec4 vert;

in vec2 texCoords;
in float depth;

out vec4 out_Color;

uniform mat4 lightViewMatrix;

void main(void)
{
    float   alpha   = 0;
    float   beta    = 0;
    vec4    kdifuse = color;
    float   factor  = 255;
    vec4    kcool   = vec4(251, 255, 117, 255)/factor;
    vec4    kwarm   = vec4(123, 117, 255, 255)/factor;

    vec3 lightDirection = vec3(vec4(lightViewMatrix * vec4(0.0, 0.0, 1.0, 0.0)).xyz);
    vec3 lightReflection = reflect(-lightDirection, normal);
    vec3 eyeDirection = -normalize(vert.xyz);
    float shininess = 80.0;

    vec4 kcdiff = kcool + alpha * kdifuse;
    vec4 kwdiff = kwarm + beta * kdifuse;
    vec4 specular = vec4(1.0) * max(pow(dot(lightReflection, eyeDirection), shininess), 0.0);

    float NL = dot(lightDirection, normal);
    vec4 kfinal = ((1 + NL)/2) * kcdiff;
    kfinal += (1 - (1+NL)/2) * kwdiff;
    kfinal += specular;
    if(dot(normal,eyeDirection)<0.5) kfinal = vec4(vec3(0), 1.0);

    out_Color = kfinal;
}
