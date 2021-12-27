//
// Created by Niskp on 02/10/2021.
//

#ifndef PAG_SHADERMANAGER_H
#define PAG_SHADERMANAGER_H

#include <map>
#include <string>
#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

namespace PAG {
	class ShaderManager {
	private:
		static ShaderManager *instancia;

		ShaderManager() = default;

		std::map<std::string, PAG::ShaderProgram *> shaderPrograms;
		std::map<std::string, PAG::Shader *> shaders;

		std::string SPActivado;
	public:
		static ShaderManager *getInstancia();

		ShaderManager(const ShaderManager &orig) = delete;

		~ShaderManager();

		void nuevoShader(const std::string &nombreShader, GLenum tipoShader, const std::string &ruta);

		void nuevoShaderProgram(const std::string &nombreSP);

		void addShaderToSP(const std::string &nombreShader, const std::string &nombreSP);

		void activarSP(const std::string &nombreSP);

		void setUniform(const std::string &nombreSP, const std::string &variable, glm::mat4 matriz);

		void setUniform(const std::string &nombreSP, const std::string &variable, glm::vec3 vec);

		void setUniform(const std::string &nombreSP, const std::string &variable, GLuint valor);

		void setUniform(const std::string &nombreSP, const std::string &variable, GLint valor);

		void setUniform(const std::string &nombreSP, const std::string &variable, float valor);

		void activarSubrutina(const std::string &nombreSP, GLenum tipoShader, const std::string &nombreSubrutina);

		void activarMultiplesSubrutinas(const std::string &nombreSP, GLenum tipoShader,
		                                const std::vector<std::string> &nombreUniform,
		                                const std::vector<std::string> &nombreSubrutina);


	};
}


#endif //PAG_SHADERMANAGER_H
