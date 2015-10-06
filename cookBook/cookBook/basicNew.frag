#version 400
in vec4 Color;
out vec4 FragColor;

void main() {
    //gl_FragColor = vec4(1.0);
   FragColor = Color;
   // FragColor = vec4(1.0 , 0.5, 1.5, 1.0);
}
