#version 400
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexColor;
layout (location = 2) in vec3 Novo;

uniform mat4 RotationMatrix;

out vec3 Color;
void main()
{
    Color = VertexColor;// + VertexPosition - VertexPosition;
    gl_Position = RotationMatrix * vec4( Novo, 1.0 );
    //gl_Position = in_Vertex_Position;
}
