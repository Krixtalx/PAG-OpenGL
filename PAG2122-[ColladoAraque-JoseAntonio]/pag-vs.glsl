#version 410
layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 normal;
uniform mat4 matrizMVP;
uniform mat4 matrizMV;

out salidaVS
{
    vec3 posicionV;
    vec3 normalV;
} salida;


void main ()
{
    gl_Position = matrizMVP * vec4 (posicion, 1);
    salida.posicionV = vec3(matrizMV * vec4(posicion, 1));
    salida.normalV = vec3(matrizMV * vec4(normal, 1));
}