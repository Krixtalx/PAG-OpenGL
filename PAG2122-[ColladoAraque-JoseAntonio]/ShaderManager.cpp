//
// Created by Niskp on 02/10/2021.
//

#include <stdexcept>
#include "ShaderManager.h"

PAG::ShaderManager *PAG::ShaderManager::instancia = nullptr;

/**
 * Consulta del objeto único de la clase
 * @return Puntero al Renderer
 */
PAG::ShaderManager *PAG::ShaderManager::getInstancia() {
	if (!instancia) {
		try {
			instancia = new ShaderManager;
		} catch (std::runtime_error &e) {
			throw e;
		}
	}
	return instancia;
}

/**
 * Destructor. Elimina todos los shaders y shaderPrograms (que estén en los mapas) del contexto OpenGL
 */
PAG::ShaderManager::~ShaderManager() {
	for (auto &shader: shaders) {
		glDeleteShader(shader.second.getShaderId());
	}

	for (auto &shaderProgram: shaderPrograms) {
		glDeleteProgram(shaderProgram.second.getIdSP());
	}
}

/**
 * Añade un nuevo shader al mapa shaders.
 * @param nombreShader nombre con el que se incluirá en el mapa
 * @param tipoShader
 * @param ruta en la que se encuentra el código fuente
 */
void PAG::ShaderManager::nuevoShader(const std::string &nombreShader, GLenum tipoShader, const std::string &ruta) {
	PAG::Shader nuevoShader(nombreShader, tipoShader, ruta);
	shaders.insert(std::make_pair(nombreShader, nuevoShader));
}

/**
 * Añade un nuevo shaderProgram al mapa shaderPrograms
 * @param nombreSP nombre con el que se incluirá en el mapa
 */
void PAG::ShaderManager::nuevoShaderProgram(const std::string &nombreSP) {
	PAG::ShaderProgram nuevoSP;
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
		SP->second.addShader(&shaders.find(nombreShader)->second);
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
	auto SP = shaderPrograms.find(nombreSP);
	if (SP != shaderPrograms.end()) {
		SP->second.activateShaderProgram();
	} else {
		throw std::runtime_error(
				"[ShaderManager]: No se ha encontrado ningun shader program con el nombre " + nombreSP);
	}
}