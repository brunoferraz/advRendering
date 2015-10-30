#version 400

in vec4 inPos;
in vec4 vel;

out vec4 nPos;


void main(void)
{
//        nPos = vec4(inPos.xyz, 1.0);
    nPos = inPos;
        //gl_Position = vec4(inPos.xyz + vec3(0, 0.01,0), 1.0);
}
