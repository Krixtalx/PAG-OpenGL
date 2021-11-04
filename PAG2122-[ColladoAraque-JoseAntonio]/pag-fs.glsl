#version 410
out vec4 colorFragmento;
in vec4 outColor;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float phong;

subroutine vec4 calcularColor ();
subroutine uniform calcularColor colorElegido;

subroutine (calcularColor)
vec4 colorDefecto ()
{
    return outColor;
}
subroutine (calcularColor)
vec4 colorMaterial ()
{
    return (vec4 (Ka, 1));
}

void main ()
{
    colorFragmento = colorElegido();
}
