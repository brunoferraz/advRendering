#version 400
layout (location = 0) in vec4 in_Position;
layout (location = 1) in vec4 in_Color;

out vec4 Color;
out vec4 Novo;

uniform float factor;

void main(void)
{
    Color = vec4(1.0, 0.0, 0.0, 1.0);
    Novo = in_Color;
    gl_Position = in_Position;
}
