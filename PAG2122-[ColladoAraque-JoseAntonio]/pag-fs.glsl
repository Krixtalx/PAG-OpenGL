#version 410
layout(location = 0) out vec4 colorFragmento;
in salidaVS
{
    vec3 posicionV;
    vec3 normalV;
} entrada;


uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform uint phong;

uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform float spotAngle;
uniform uint expBordes;

uniform vec3 posLuz;
uniform vec3 dirLuz;


subroutine vec3 calcularLuz();
subroutine uniform calcularLuz luzElegida;

subroutine (calcularLuz)
vec3 colorDefecto ()
{
    return vec3(1, 0, 0);
}

subroutine (calcularLuz)
vec3 luzAmbiente()
{
    return Ka*Ia;
}

subroutine (calcularLuz)
vec3 luzPuntual()
{
    vec3 n = normalize(entrada.normalV);

    vec3 l = normalize(posLuz-entrada.posicionV);
    vec3 v = normalize(-entrada.posicionV);
    vec3 r = reflect(-l, n);

    vec3 difusa = (Id * Kd * max(dot(l, n), 0.0));
    vec3 especular = (Is * Ks * pow(max(dot(r, v), 0.0), phong));

    return difusa + especular;
}

subroutine (calcularLuz)
vec3 luzDireccional ()
{
    vec3 n = normalize(entrada.normalV);

    vec3 l = -dirLuz;
    vec3 v = normalize(-entrada.posicionV);
    vec3 r = reflect(-l, n);

    vec3 difusa = (Id * Kd * max(dot(l, n), 0.0));
    vec3 especular = (Is * Ks * pow(max(dot(r, v), 0.0), phong));

    return difusa + especular;
}

subroutine (calcularLuz)
vec3 luzFoco ()
{
    vec3 l = normalize(posLuz-entrada.posicionV);
    vec3 d = dirLuz;
    float cosGamma = cos(spotAngle);
    float cosDelta = cos(dot(-l, d));
    float spotFactor = pow(cosDelta, expBordes);
    if (dot(-l, d) < cosGamma) { spotFactor = 0.0; }
    vec3 n = normalize(entrada.normalV);
    vec3 v = normalize(-entrada.posicionV);
    vec3 r = reflect(-l, n);

    vec3 difusa = (Id * Kd * max(dot(l, n), 0.0));
    vec3 especular = (Is * Ks * pow(max(dot(r, v), 0.0), phong));

    return spotFactor * (difusa + especular);
}

void main ()
{
    colorFragmento = vec4(luzElegida(), 1);
}