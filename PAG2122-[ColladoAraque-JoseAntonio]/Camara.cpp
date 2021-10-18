//
// Created by Niskp on 18/10/2021.
//

#include "cmath"
#include "Camara.h"
#include "RenderOptions.h"
#include <glm/gtx/transform.hpp>
#include <glm/ext/vector_relational.hpp>


/**
 * Constructor por defecto. Inicializa la cámara con unos parametros predeterminados
 */
PAG::Camara::Camara() : posicion(0, 0, 2.5f), puntoMira(0, 0, 0),
                        up(0, 1, 0), zNear(0.1f), zFar(10), alto(PAG::altoVentanaPorDefecto),
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
 * Calcula la matriz de modelado visión y proyección y la devuelve
 * @return matrizMVP
 */
glm::mat4 PAG::Camara::matrizMVP() const {
	glm::mat4 vision = glm::lookAt(posicion, puntoMira, up);
	glm::mat4 proyeccion = glm::perspective(fovY, aspecto(), zNear, zFar);
	//Multiplicamos de manera inversa: Modelado-Vision-Proyeccion -> Proyeccion-Vision-Modelado
	return proyeccion * vision;
}

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

void PAG::Camara::calcularFovY() {
	this->fovY = 2 * glm::atan(tan(this->fovX / 2) / aspecto());
}


/**
 * ------------------------------Movimientos de la camara------------------------
 */

/**
 * Movimiento truck de la camara. Mueve la camara hacia delante o hacia atrás
 * @param mov
 */
void PAG::Camara::truck(float mov) {
	glm::mat4 translacion = glm::translate(n * mov);
	posicion = glm::vec3(translacion * glm::vec4(posicion, 1));
	puntoMira = glm::vec3(translacion * glm::vec4(puntoMira, 1));
}

void PAG::Camara::dolly(float mov) {
	glm::mat4 translacion = glm::translate(u * mov);
	posicion = glm::vec3(translacion * glm::vec4(posicion, 1));
	puntoMira = glm::vec3(translacion * glm::vec4(puntoMira, 1));
}

void PAG::Camara::boom(float mov) {
	glm::mat4 translacion = glm::translate(v * mov);
	posicion = glm::vec3(translacion * glm::vec4(posicion, 1));
	puntoMira = glm::vec3(translacion * glm::vec4(puntoMira, 1));
}

void PAG::Camara::crane(float mov) {
	boom(-mov);
}

void PAG::Camara::zoom(float mov) {
	fovX += glm::radians(mov);
	if (fovX < 0)
		fovX = 0;
	if (fovX > glm::pi<float>())
		fovX = glm::pi<float>();
	
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
