#version 410
layout (location = 0) in vec3 posicion;
out vec4 color;
void main ()
{
    gl_Position = vec4 (posicion, 1);
    color = vec4(posicion, 1);
}
