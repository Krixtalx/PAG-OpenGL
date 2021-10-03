//
// Created by Niskp on 01/10/2021.
//

#ifndef PAG_SHADERPROGRAM_H
#define PAG_SHADERPROGRAM_H


#include <GL/glew.h>
#include "Shader.h"
#include <vector>

namespace PAG {
	class ShaderProgram {
	private:
		GLuint idSP;
		std::vector<Shader *> shaders;
		bool linked = false;

		void compruebaErroresSP() const;

	public:
		ShaderProgram();

		ShaderProgram(std::vector<Shader *> shaders);

		void addShader(Shader *shader);

		void activateShaderProgram();

		GLuint getIdSP() const;

	};
}


#endif //PAG_SHADERPROGRAM_H
