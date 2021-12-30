//
// Created by Niskp on 14/11/2021.
//

#include <stdexcept>
#include "Luz.h"
#include "ShaderManager.h"

/**
 * Constructor parametrizado para una luz ambiente
 * @param ia color ambiente de la luz
 */
PAG::Luz::Luz(const glm::vec3 &ia) : ia(ia), tipoLuz(PAG::tipoLuz::ambiente) { inicializarMapaSombras(); }


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
	inicializarMapaSombras();
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
	inicializarMapaSombras();
}

void PAG::Luz::aplicarLuz(const std::string &shader, const glm::mat4 &matriz) const {
	PAG::ShaderManager::getInstancia()->activarSP(shader);
	if (this->tipoLuz == PAG::tipoLuz::ambiente) {
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Ia", ia);
	} else if (this->tipoLuz == PAG::tipoLuz::puntual) {
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Id", id);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Is", is);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "posLuz", glm::vec3(matriz * glm::vec4(posicion, 1)));
	} else if (this->tipoLuz == PAG::tipoLuz::direccional) {
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Id", id);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Is", is);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "dirLuz", glm::normalize(glm::vec3(
				glm::transpose(glm::inverse(matriz)) * glm::vec4(direccion, 0))));
	} else if (this->tipoLuz == PAG::tipoLuz::foco) {
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Id", id);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "Is", is);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "posLuz", glm::vec3(matriz * glm::vec4(posicion, 1)));
		PAG::ShaderManager::getInstancia()->setUniform(shader, "dirLuz", glm::normalize(glm::vec3(
				glm::transpose(glm::inverse(matriz)) * glm::vec4(direccion, 0))));
		PAG::ShaderManager::getInstancia()->setUniform(shader, "spotAngle", gamma);
		PAG::ShaderManager::getInstancia()->setUniform(shader, "expBordes", exponenteBordes);
	}
	//Activamos el muestrador aunque no se use mapa de sombras para evitar undefined behaviours de OpenGL.
	//https://stackoverflow.com/a/45203667
	ShaderManager::getInstancia()->setUniform(shader, "muestreadorSombra", (GLint) 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, idMapaSombras);
}

/**
 * Inicializa los elementos propios de la luz para crear el mapa de sombras (Generar el id de textura y configurarla)
 */
void PAG::Luz::inicializarMapaSombras() {
	glGenTextures(1, &idMapaSombras);
	GLfloat borde[] = {1.0, 1.0, 1.0, 1.0};

	//Generamos un mapa de sombras para cada luz, aunque realmente no lo use.
	// Esto se hace para evitar undefined behaviours de OpenGL por no asignar una textura al muestreador de sombras
	//https://stackoverflow.com/a/45203667
	glBindTexture(GL_TEXTURE_2D, idMapaSombras);
	if (tipoLuz == tipoLuz::direccional || tipoLuz == tipoLuz::foco)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, PAG::anchoMS, PAG::altoMS, 0,
		             GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
	else //Hacemos que la textura no usada sea 1x1 para evitar consumo excesivo de VRAM
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 1, 1, 0,
		             GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borde);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE,
	                GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);
}

/**
 * Genera la matriz de visión y proyección necesaria para calcular el mapa de sombras de dicha luz
 * @return matriz VP
 */
glm::mat4 PAG::Luz::generarMatrizVPMS() const {
	if (tipoLuz == PAG::tipoLuz::direccional) {
		glm::mat4 matriz = glm::ortho(-3.0, 3.0, -3.0, 3.0, 0.1, 10.0);
		matriz *= glm::lookAt(glm::vec3(2.0) * (-direccion), glm::vec3(0, 0, 0),
		                      glm::vec3(0, 1, 0));
		return matriz;
	}
	if (tipoLuz == PAG::tipoLuz::foco) {
		glm::mat4 matriz = glm::perspective(2 * gamma, (float) PAG::anchoMS / (float) PAG::altoMS, 0.1f,
		                                    10.0f);
		matriz *= glm::lookAt(posicion, posicion + direccion, glm::vec3(0, 1, 0));

		return matriz;
	}
	throw std::runtime_error(
			"[Luz::generarMatrizVPMS]: Se ha intentado generar la matriz con un tipo de luz no compatible");
}

PAG::tipoLuz PAG::Luz::getTipoLuz() const {
	return tipoLuz;
}

bool PAG::Luz::emiteSombras() const {
	return tipoLuz == PAG::tipoLuz::direccional || tipoLuz == PAG::tipoLuz::foco;
}

GLuint PAG::Luz::getIdMapaSombras() const {
	return idMapaSombras;
}
