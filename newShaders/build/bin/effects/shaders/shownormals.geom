#version 430
layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

in vec4 colorVert[3];
in vec3 normalVert[3];

out vec4 colorFrag;
out vec3 normalFrag;

void main() {
    colorFrag = vec4(1, 0, 0, 1);
/*
    gl_Position = gl_in[0].gl_Position;
    //colorFrag = colorVert[0];
    normalFrag = normalVert[0];
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    //colorFrag = colorVert[1];
    normalFrag = normalVert[1];
    EmitVertex();
*/

    vec4 vert0 = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position)/3;
    gl_Position = vert0;
    EmitVertex();

    vec3 normalFace = (normalVert[0] +  normalVert[1] + normalVert[2])/3;
    vec4 vert1 = vec4(normalFace/1000,1.0);
    vec4 v0 = gl_in[0].gl_Position - vec4(normalVert[0]/100,1);
    vec4 v1 = gl_in[1].gl_Position - vec4(normalVert[1]/100,1);
    vec4 v2 = gl_in[2].gl_Position - vec4(normalVert[2]/100,1);

    vec4 vf = (v0 + v1+ v2)/3;

    gl_Position = vf;
    EmitVertex();

    EndPrimitive();
}
