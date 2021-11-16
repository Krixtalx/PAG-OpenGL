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
              float gamma, GLuint exponenteBordes) : id(id), is(is), posicion(posicion), direccion(direccion),
                                                    exponenteBordes(exponenteBordes),
                                                    tipoLuz(PAG::tipoLuz::foco) {
	this->gamma = glm::radians(gamma);
}

void PAG::Luz::aplicarLuz(const std::string &shader, const glm::mat4 &matriz) const {
	PAG::ShaderManager::getInstancia()->activarSP(shader);
	if (this->tipoLuz == PAG::tipoLuz::ambiente) {
		PAG::ShaderManager::getInstancia()->activarSubrutina(shader, GL_FRAGMENT_SHADER, "luzAmbiente");
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Ia", ia);
	} else if (this->tipoLuz == PAG::tipoLuz::puntual) {
		PAG::ShaderManager::getInstancia()->activarSubrutina(shader, GL_FRAGMENT_SHADER, "luzPuntual");
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Id", id);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Is", is);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "posLuz", glm::vec3(matriz * glm::vec4(posicion, 1)));
	} else if (this->tipoLuz == PAG::tipoLuz::direccional) {
		PAG::ShaderManager::getInstancia()->activarSubrutina(shader, GL_FRAGMENT_SHADER, "luzDireccional");
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Id", id);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Is", is);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "dirLuz", glm::vec3(
				glm::transpose(glm::inverse(matriz)) * glm::vec4(direccion, 0)));
	} else {
		PAG::ShaderManager::getInstancia()->activarSubrutina(shader, GL_FRAGMENT_SHADER, "luzFoco");
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Id", id);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Is", is);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "posLuz", glm::vec3(matriz * glm::vec4(posicion, 1)));
		PAG::ShaderManager::getInstancia()->setUniform(shader, "dirLuz", glm::vec3(
				glm::transpose(glm::inverse(matriz)) * glm::vec4(direccion, 0)));
		PAG::ShaderManager::getInstancia()->setUniform(shader, "spotAngle", gamma);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "expBordes", exponenteBordes);
	}
}
