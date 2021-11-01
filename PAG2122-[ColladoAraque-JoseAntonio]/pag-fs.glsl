#version 410
out vec4 colorFragmento;
in vec4 outColor;
void main ()
{
    colorFragmento = outColor;
}
