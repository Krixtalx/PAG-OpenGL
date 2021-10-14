//
// Created by Niskp on 02/10/2021.
//

#ifndef PAG_SHADERMANAGER_H
#define PAG_SHADERMANAGER_H

#include <map>
#include <string>
#include "ShaderProgram.h"

namespace PAG {
	class ShaderManager {
	private:
		static ShaderManager *instancia;

		ShaderManager() = default;

		std::map<std::string, PAG::ShaderProgram*> shaderPrograms;
		std::map<std::string, PAG::Shader*> shaders;
	public:
		static ShaderManager *getInstancia();

		ShaderManager(const ShaderManager &orig) = delete;

		~ShaderManager();

		void nuevoShader(const std::string &nombreShader, GLenum tipoShader, const std::string &ruta);

		void nuevoShaderProgram(const std::string &nombreSP);

		void addShaderToSP(const std::string &nombreShader, const std::string &nombreSP);

		void activarSP(const std::string &nombreSP);

	};
}


#endif //PAG_SHADERMANAGER_H
