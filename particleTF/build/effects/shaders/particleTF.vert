#version 400

subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;

in vec4 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoords;
in vec4 in_Color;
in vec4 in_Velocity;

out vec4 color;
out vec3 normal;
out vec4 vert;
out vec2 texCoords;

out float depth;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec4 default_color;

// if attribute in_Color exists or not
uniform bool has_color;

out vec3 Position;
out vec3 Velocity;

subroutine (RenderPassType)
void update(){
    Position = in_Position.xyz + in_Velocity.xyz;
}
subroutine (RenderPassType)
void render(){
    mat4 modelView = modelMatrix * viewMatrix;
    gl_Position = modelView * projectionMatrix * in_Position;
}

void main(void)
{
    RenderPass();
}
