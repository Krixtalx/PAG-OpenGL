//
// Created by Niskp on 02/10/2021.
//

#include <stdexcept>
#include "ShaderManager.h"

PAG::ShaderManager *PAG::ShaderManager::instancia = nullptr;

PAG::ShaderManager::ShaderManager() = default;

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


PAG::ShaderManager::~ShaderManager() {
	for (auto &shader: shaders) {
		glDeleteShader(shader.second.getShaderId());
	}

	for (auto &shaderProgram: shaderPrograms) {
		glDeleteProgram(shaderProgram.second.getIdSP());
	}
}

void PAG::ShaderManager::nuevoShader(const std::string &nombreShader, GLenum tipoShader, const std::string &ruta) {
	PAG::Shader nuevoShader(nombreShader, tipoShader, ruta);
	shaders.insert(std::pair<std::string, PAG::Shader>(nombreShader, nuevoShader));
}

void PAG::ShaderManager::nuevoShaderProgram(const std::string &nombreSP) {
	PAG::ShaderProgram nuevoSP;
	shaderPrograms.insert(std::pair<std::string, PAG::ShaderProgram>(nombreSP, nuevoSP));
}

void PAG::ShaderManager::addShaderToSP(const std::string &nombreShader, const std::string &nombreSP) {
	shaderPrograms.find(nombreSP)->second.addShader(&shaders.find(nombreShader)->second);
}

void PAG::ShaderManager::activarSP(const std::string &nombreSP) {
	shaderPrograms.find(nombreSP)->second.activateShaderProgram();
}