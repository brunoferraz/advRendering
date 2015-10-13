#version 400
layout (location = 0) in vec4 in_Vertex_Position;
layout (location = 1) in vec4 in_Vertex_Color;

out vec4 Color;

uniform mat4 RotationMatrix;

void main()
{
//    Color = vec4(1.0, 0.0, 0.0, 1.0);
    Color = in_Vertex_Color;// + VertexPosition - VertexPosition;
    //gl_Position = RotationMatrix * vec4( Novo, 1.0 );
    gl_Position = vec4(in_Vertex_Position.xyz, 1.0);
}
