#version 430
layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

in vec4 colorVert[3];
in vec3 normalVert[3];
in vec4 vert[3];

out vec4 colorFrag;
out vec3 normalFrag;
uniform mat4 projectionMatrix;

void main() {
    colorFrag = vec4(1, 0, 0, 1);

    vec4 vert0 = (vert[0] + vert[1] + vert[2])/3;
    vert0.w = 1;
    gl_Position = projectionMatrix * vert0;
    EmitVertex();

    vec3 nf0 = (normalVert[0] * 0.5) + (normalVert[1] * 0.5);
    vec3 nf = (nf0 * 0.5) + (normalVert[2] * 0.5);
    nf/= 10;

    gl_Position = projectionMatrix * (vert0 + vec4(nf, 1));
    EmitVertex();

    EndPrimitive();
}
