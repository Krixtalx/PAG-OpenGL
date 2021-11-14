//
// Created by Niskp on 14/11/2021.
//

#include "Luz.h"
#include "ShaderManager.h"

/**
 * Constructor parametrizado para una luz ambiente
 * @param ia color ambiente de la luz
 */
PAG::Luz::Luz(const glm::vec3 &ia) : ia(ia), tipoLuz(PAG::tipoLuz::ambiente) {}


/**
 * Constructor parametrizado para una luz puntual o luz direccional
 * @param id color difuso de la luz
 * @param is color especular de la luz
 * @param posicionOdireccion vec3 que indica la posicion o la direccion dependiendo del tipo de luz
 * @param puntual true si es una luz puntual. False en caso de que sea una luz direccional
 */
PAG::Luz::Luz(const glm::vec3 &id, const glm::vec3 &is, const glm::vec3 &posicionOdireccion, const bool &puntual) : id(
		id), is(is) {
	if (puntual) {
		posicion = posicionOdireccion;
		tipoLuz = PAG::tipoLuz::puntual;
	} else {
		direccion = posicionOdireccion;
		tipoLuz = PAG::tipoLuz::direccional;
	}
}

/**
 * Constructor parametrizado para una luz de tipo foco
 * @param id color difuso de la luz
 * @param is color especular de la luz
 * @param posicion posición de la luz
 * @param direccion dirección a la que apunta el foco
 * @param gamma angulo de apertura del cono de luz
 * @param exponenteBordes exponente para el calculo de los bordes suaves en el cono de luz
 */
PAG::Luz::Luz(const glm::vec3 &id, const glm::vec3 &is, const glm::vec3 &posicion, const glm::vec3 &direccion,
              float gamma, float exponenteBordes) : id(id), is(is), posicion(posicion), direccion(direccion),
                                                    gamma(gamma), exponenteBordes(exponenteBordes),
                                                    tipoLuz(PAG::tipoLuz::foco) {}

void PAG::Luz::aplicarLuz(std::string shader) {
	if (this->tipoLuz == PAG::tipoLuz::ambiente) {
		//PAG::ShaderManager::getInstancia()->
	}
}
