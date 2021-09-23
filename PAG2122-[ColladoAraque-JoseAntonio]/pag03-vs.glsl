#version 410
layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 color;
out vec4 outColor;
void main ()
{
    gl_Position = vec4 (posicion, 1);
    outColor = vec4(color, 1);
}
