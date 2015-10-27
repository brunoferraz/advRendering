#version 400

in vec4 in_Position;
in vec4 vel;
out vec4 nPos;


void main(void)
{
        nPos = vec4(in_Position.xyz, 1.0);
        gl_Position = in_Position;
}
