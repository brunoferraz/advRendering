#version 400
in vec4 in_Position;
in vec4 in_Color;

out vec4 Color;
out vec4 Novo;

uniform float factor;

void main(void)
{
    if(factor==1.0){
        Color = vec4(1.0, 0.0, 0.0, 1.0);
    }else{
        Novo = in_Color;
    }
    gl_Position = in_Position;
}

