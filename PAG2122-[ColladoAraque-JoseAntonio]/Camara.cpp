//
// Created by Niskp on 18/10/2021.
//

#define GLM_ENABLE_EXPERIMENTAL

#include "cmath"
#include "Camara.h"
#include "RenderOptions.h"
#include <glm/gtx/transform.hpp>
#include <glm/ext/vector_relational.hpp>
#include <iostream>
#include "glm/gtx/string_cast.hpp"


/**
 * Constructor por defecto. Inicializa la cámara con unos parametros predeterminados
 */
PAG::Camara::Camara() : posicion(0, 0, 2.5f), puntoMira(0, 0, 0),
                        up(0, 1, 0), zNear(0.1f), zFar(200), alto(PAG::altoVentanaPorDefecto),
                        ancho(PAG::anchoVentanaPorDefecto) {

	fovX = glm::radians(80.0);
	calcularFovY();
	calcularEjes();
}

/**
 * Constructor parametrizado. Inicializa la cámara con los parametros que se pasan como parametro
 * @param posicion en la que se establecerá la camara
 * @param puntoMira punto al que mira la camara
 * @param up vector que indica la dirección "arriba" de la camara
 * @param zNear plano de clipping cercano
 * @param zFar plano de clipping lejano
 * @param fovX campo de visión en el eje X
 * @param alto del viewport
 * @param ancho del viewport
 */
PAG::Camara::Camara(const glm::vec3 &posicion, const glm::vec3 &puntoMira, const glm::vec3 &up, GLfloat zNear,
                    GLfloat zFar, GLfloat fovX, GLuint alto, GLuint ancho) : posicion(posicion), puntoMira(puntoMira),
                                                                             up(up), zNear(zNear), zFar(zFar),
                                                                             alto(alto), ancho(ancho) {
	this->fovX = glm::radians(fovX);
	calcularFovY();
	calcularEjes();
}

/**
 * Calcula la matriz de modelado visión y proyección y la devuelve.
 * @return matrizMVP
 */
glm::mat4 PAG::Camara::matrizMVP() const {
	glm::mat4 vision = glm::lookAt(posicion, puntoMira, up);
	glm::mat4 proyeccion = glm::perspective(fovY, aspecto(), zNear, zFar);
	//Multiplicamos de manera inversa: Modelado-Vision-Proyeccion -> Proyeccion-Vision-Modelado
	return proyeccion * vision; //Devuelve solo proyección*vision. El modelado lo aplicará el modelo
}

/**
 * Calcula la matriz de modelado y visión y la devuelve.
 * @return matrizMV
 */
glm::mat4 PAG::Camara::matrizMV() const {
	return glm::lookAt(posicion, puntoMira, up); //Devuelve solo vision. El modelado lo aplicará el modelo
}

/**
 * Actualiza los ejes locales de la cámara recalculando su valor.
 */
void PAG::Camara::calcularEjes() {
	n = glm::normalize(posicion - puntoMira);

	if (glm::all(glm::equal(n, up, 0.001f))) {
		u = glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), n));
	} else if (glm::all(glm::equal(n, -up, 0.001f))) {
		u = glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), n));
	} else {
		u = glm::normalize(glm::cross(up, n));
	}
	v = glm::normalize(glm::cross(n, u));
}

/**
 * Calcula el fovY equivalente al fovX actual
 */
void PAG::Camara::calcularFovY() {
	this->fovY = 2 * glm::atan(tan(this->fovX / 2) / aspecto());
}


/**
 * ------------------------------Movimientos de la camara------------------------
 */

/**
 * Movimiento truck de la camara. Mueve la camara hacia delante o hacia atrás
 * @param mov magnitud del movimiento
 */
void PAG::Camara::truck(float mov) {
	posicion[2] += mov;
	puntoMira[2] += mov;
}

/**
 * Movimiento dolly de la camara. Mueve la camara hacia la izquierda o hacia la derecha
 * @param mov magnitud del movimiento
 */
void PAG::Camara::dolly(float mov) {
	posicion[0] += mov;
	puntoMira[0] += mov;
}

/**
 * Movimiento boom de la cámara. Mueve la cámara hacia arriba
 * @param mov magnitud del movimiento
 */
void PAG::Camara::boom(float mov) {
	posicion[1] += mov;
	puntoMira[1] += mov;
}

/**
 * Movimiento boom de la cámara. Mueve la cámara hacia abajo
 * @param mov magnitud del movimiento
 */
void PAG::Camara::crane(float mov) {
	boom(-mov);
}

/**
 * Movimiento pan de la cámara. Rota la cámara horizontalmente
 * @param mov magnitud del movimiento
 */
void PAG::Camara::pan(float mov) {
	glm::mat4 rotacion = glm::rotate(glm::radians(mov * 0.02f), v);
	puntoMira = glm::vec3(rotacion * glm::vec4(puntoMira - posicion, 1)) + posicion;
	calcularEjes();
}

/**
 * Movimiento tilt de la cámara. Rota la cámara verticalmente
 * @param mov magnitud del movimiento
 */
void PAG::Camara::tilt(float mov) {
	glm::mat4 rotacion = glm::rotate(glm::radians(mov * 0.02f), u);
	puntoMira = glm::vec3(rotacion * glm::vec4(puntoMira - posicion, 1)) + posicion;
	calcularEjes();
	up = v; // Igualamos up a v para evitar que n pueda ser igual a up. Ver explicación en la documentación
}

/**
 * Orbita en longitud alrededor del punto al que se mira.
 * @param mov magnitud del movimiento
 */
void PAG::Camara::orbitX(float mov) {
	glm::mat4 rotacion = glm::rotate(glm::radians(mov), v);
	posicion = glm::vec3(rotacion * glm::vec4(posicion - puntoMira, 1)) + puntoMira;
	calcularEjes();
}

/**
 * Orbita en latitud alrededor del punto al que se mira.
 * @param mov magnitud del movimiento
 */
void PAG::Camara::orbitY(float mov) {
	glm::mat4 rotacion = glm::rotate(glm::radians(mov), u);
	posicion = glm::vec3(rotacion * glm::vec4(posicion - puntoMira, 1)) + puntoMira;
	calcularEjes();
	up = v; // Igualamos up a v para evitar que n pueda ser igual a up. Ver explicación en la documentación
}

/**
 * Realiza el zoom modificando el fov
 * @param angulo variación del ángulo
 */
void PAG::Camara::zoom(float angulo) {
	fovX += glm::radians(angulo);
	if (fovX < 0)
		fovX = 0;
	if (fovX > glm::pi<float>())
		fovX = glm::pi<float>();

	calcularFovY();
}

/**
 * Situa la cámara en la posición por defecto.
 */
void PAG::Camara::reset() {
	posicion = glm::vec3(0, 0, 2.5);
	puntoMira = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 1, 0);
	fovX = glm::radians(80.0f);
	calcularEjes();
	calcularFovY();
}


/**
 * ------------------------------Getters y setters------------------------
 */

/**
 * Calcula y devuelve la relacion de aspecto
 * @return relacion de aspecto del viewport
 */
GLfloat PAG::Camara::aspecto() const {
	return ((GLfloat) ancho / (GLfloat) alto);
}

void PAG::Camara::setAlto(GLuint alto) {
	Camara::alto = alto;
}

void PAG::Camara::setAncho(GLuint ancho) {
	Camara::ancho = ancho;
}