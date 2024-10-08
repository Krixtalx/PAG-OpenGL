//
// Created by Niskp on 02/10/2021.
//

#include <stdexcept>
#include "ShaderManager.h"

PAG::ShaderManager *PAG::ShaderManager::instancia = nullptr;

/**
 * Consulta del objeto único de la clase
 * @return Puntero al ShaderManager
 */
PAG::ShaderManager *PAG::ShaderManager::getInstancia() {
	if (!instancia) {
		instancia = new ShaderManager;
	}
	return instancia;
}

/**
 * Destructor. Elimina todos los shaders y shaderPrograms (que estén en los mapas) del contexto OpenGL
 */
PAG::ShaderManager::~ShaderManager() {
	for (auto &shader: shaders) {
		delete shader.second;
	}

	for (auto &shaderProgram: shaderPrograms) {
		delete shaderProgram.second;
	}
}

/**
 * Añade un nuevo shader al mapa shaders.
 * @param nombreShader nombre con el que se incluirá en el mapa
 * @param tipoShader
 * @param ruta en la que se encuentra el código fuente
 */
void PAG::ShaderManager::nuevoShader(const std::string &nombreShader, GLenum tipoShader, const std::string &ruta) {
	auto nuevoShader = new Shader(nombreShader, tipoShader, ruta);
	shaders.insert(std::make_pair(nombreShader, nuevoShader));
}

/**
 * Añade un nuevo shaderProgram al mapa shaderPrograms
 * @param nombreSP nombre con el que se incluirá en el mapa
 */
void PAG::ShaderManager::nuevoShaderProgram(const std::string &nombreSP) {
	auto nuevoSP = new ShaderProgram();
	shaderPrograms.insert(std::make_pair(nombreSP, nuevoSP));
}

/**
 * Añade el shader al shader program indicado
 * @param nombreShader a añadir
 * @param nombreSP al que se le añadirá
 */
void PAG::ShaderManager::addShaderToSP(const std::string &nombreShader, const std::string &nombreSP) {
	auto SP = shaderPrograms.find(nombreSP);
	if (SP != shaderPrograms.end()) {
		SP->second->addShader(shaders.find(nombreShader)->second);
	} else {
		throw std::runtime_error(
				"[ShaderManager]: No se ha encontrado ningun shader program con el nombre " + nombreSP);
	}
}

/**
 * Activa el shader program indicado
 * @param nombreSP a activar
 */
void PAG::ShaderManager::activarSP(const std::string &nombreSP) {
	if (nombreSP != SPActivado) {
		auto SP = shaderPrograms.find(nombreSP);
		if (SP != shaderPrograms.end()) {
			SP->second->activateShaderProgram();
			SPActivado = nombreSP;
		} else {
			throw std::runtime_error(
					"[ShaderManager]: No se ha encontrado ningun shader program con el nombre " + nombreSP);
		}
	}
}

/**
 * Método para establecer una variable uniform dentro de un Shader Program
 * @param nombreSP nombre del ShaderProgram en el que establecer el uniform
 * @param variable nombre de la variable a establecer
 */
void PAG::ShaderManager::setUniform(const std::string &nombreSP, const std::string &variable, glm::mat4 matriz) {
	auto SP = shaderPrograms.find(nombreSP);
	if (SP != shaderPrograms.end()) {
		GLint location = glGetUniformLocation(SP->second->getIdSP(), variable.c_str());
		if (location >= 0) {
			glUniformMatrix4fv(location, 1, false, glm::value_ptr(matriz));
		} else
			throw std::runtime_error(
					"[ShaderManager]: No se ha encontrado ninguna variable con el nombre " + variable +
					" en el shaderProgram " + nombreSP);
	} else {
		throw std::runtime_error(
				"[ShaderManager]: No se ha encontrado ningun shader program con el nombre " + nombreSP);
	}

}

/**
 * Método para establecer una variable uniform dentro de un Shader Program
 * @param nombreSP nombre del ShaderProgram en el que establecer el uniform
 * @param variable nombre de la variable a establecer
 */
void PAG::ShaderManager::setUniform(const std::string &nombreSP, const std::string &variable, glm::vec3 vec) {
	auto SP = shaderPrograms.find(nombreSP);
	if (SP != shaderPrograms.end()) {
		GLint location = glGetUniformLocation(SP->second->getIdSP(), variable.c_str());
		if (location >= 0) {
			glUniform3fv(location, 1, glm::value_ptr(vec));
		} else
			throw std::runtime_error(
					"[ShaderManager]: No se ha encontrado ninguna variable con el nombre " + variable +
					" en el shaderProgram " + nombreSP);
	} else {
		throw std::runtime_error(
				"[ShaderManager]: No se ha encontrado ningun shader program con el nombre " + nombreSP);
	}
}

/**
 * Método para establecer una variable uniform dentro de un Shader Program
 * @param nombreSP nombre del ShaderProgram en el que establecer el uniform
 * @param variable nombre de la variable a establecer
 */
void PAG::ShaderManager::setUniform(const std::string &nombreSP, const std::string &variable, GLuint valor) {
	auto SP = shaderPrograms.find(nombreSP);
	if (SP != shaderPrograms.end()) {
		GLint location = glGetUniformLocation(SP->second->getIdSP(), variable.c_str());
		if (location >= 0) {
			glUniform1ui(location, valor);
		} else
			throw std::runtime_error(
					"[ShaderManager]: No se ha encontrado ninguna variable con el nombre " + variable +
					" en el shaderProgram " + nombreSP);
	} else {
		throw std::runtime_error(
				"[ShaderManager]: No se ha encontrado ningun shader program con el nombre " + nombreSP);
	}
}

/**
 * Método para establecer una variable uniform dentro de un Shader Program
 * @param nombreSP nombre del ShaderProgram en el que establecer el uniform
 * @param variable nombre de la variable a establecer
 */
void PAG::ShaderManager::setUniform(const std::string &nombreSP, const std::string &variable, GLint valor) {
	auto SP = shaderPrograms.find(nombreSP);
	if (SP != shaderPrograms.end()) {
		GLint location = glGetUniformLocation(SP->second->getIdSP(), variable.c_str());
		if (location >= 0) {
			glUniform1i(location, valor);
		} else
			throw std::runtime_error(
					"[ShaderManager]: No se ha encontrado ninguna variable con el nombre " + variable +
					" en el shaderProgram " + nombreSP);
	} else {
		throw std::runtime_error(
				"[ShaderManager]: No se ha encontrado ningun shader program con el nombre " + nombreSP);
	}
}

void PAG::ShaderManager::setUniform(const std::string &nombreSP, const std::string &variable, float valor) {
	auto SP = shaderPrograms.find(nombreSP);
	if (SP != shaderPrograms.end()) {
		GLint location = glGetUniformLocation(SP->second->getIdSP(), variable.c_str());
		if (location >= 0) {
			glUniform1f(location, valor);
		} else
			throw std::runtime_error(
					"[ShaderManager]: No se ha encontrado ninguna variable con el nombre " + variable +
					" en el shaderProgram " + nombreSP);
	} else {
		throw std::runtime_error(
				"[ShaderManager]: No se ha encontrado ningun shader program con el nombre " + nombreSP);
	}
}

/**
 * Método que permite activar una subrutina en determinado ShaderProgram
 * @param nombreSP nombre del ShaderProgram al que se le activará la subrutina
 * @param tipoShader en que shader se encuentra la subrutina (GL_VERTEX_SHADER o GL_FRAGMENT_SHADER)
 * @param nombreSubrutina nombre de la subrutina a activar
 */
void PAG::ShaderManager::activarSubrutina(const std::string &nombreSP, GLenum tipoShader,
                                          const std::string &nombreSubrutina) {
	auto SP = shaderPrograms.find(nombreSP);
	if (SP != shaderPrograms.end()) {
		GLuint location = glGetSubroutineIndex(SP->second->getIdSP(), tipoShader, nombreSubrutina.c_str());
		glUniformSubroutinesuiv(tipoShader, 1, &location);
	} else {
		throw std::runtime_error(
				"[ShaderManager]: No se ha encontrado ningun shader program con el nombre " + nombreSP);
	}
}

/**
 * Método que permite activar varias subrutinas en determinado ShaderProgram
 * @param nombreSP nombre del ShaderProgram al que se le activará la subrutina
 * @param tipoShader en que shader se encuentra la subrutina (GL_VERTEX_SHADER o GL_FRAGMENT_SHADER)
 * @param nombreUniform nombres de los uniforms a activar
 * @param nombreSubrutina nombres de la subrutinas a activar
 */
void PAG::ShaderManager::activarMultiplesSubrutinas(const std::string &nombreSP, GLenum tipoShader,
                                                    const std::vector<std::string> &nombreUniform,
                                                    const std::vector<std::string> &nombreSubrutina) {
	auto SP = shaderPrograms.find(nombreSP);
	if (SP != shaderPrograms.end()) {
		if (nombreUniform.size() != nombreSubrutina.size())
			throw std::runtime_error(
					"[ShaderManager::MultiplesSubrutinas]: No se ha pasado el mismo nº de uniforms que de subrutinas");

		GLint tam = 0;
		glGetProgramStageiv(SP->second->getIdSP(), GL_FRAGMENT_SHADER,
		                    GL_ACTIVE_SUBROUTINE_UNIFORMS, &tam);

		if (nombreUniform.size() != tam)
			throw std::runtime_error(
					"[ShaderManager::MultiplesSubrutinas]: No coincide el nº de uniforms pasados con el nº de uniforms en el shader");

		GLuint *valores = new GLuint[tam];
		for (int i = 0; i < tam; ++i) {
			GLint posUniform = glGetSubroutineUniformLocation(SP->second->getIdSP(), tipoShader,
			                                                  nombreUniform[i].c_str());
			if (posUniform == -1) {
				throw std::runtime_error("[ShaderManager::MultiplesSubrutinas]: No se ha podido localizar el uniform " +
				                         nombreUniform[i] + " en " + nombreSP);
			}
			GLuint location = glGetSubroutineIndex(SP->second->getIdSP(), tipoShader, nombreSubrutina[i].c_str());
			if (location == GL_INVALID_INDEX) {
				throw std::runtime_error(
						"[ShaderManager::MultiplesSubrutinas]: No se ha podido localizar la implementación " +
						nombreSubrutina[i] + " de " + nombreUniform[i] + " en " + nombreSP);
			}
			valores[posUniform] = location;
		}

		glUniformSubroutinesuiv(tipoShader, tam, valores);
		delete[] valores;
	} else {
		throw std::runtime_error(
				"[ShaderManager]: No se ha encontrado ningun shader program con el nombre " + nombreSP);
	}
}