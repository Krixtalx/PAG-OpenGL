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
		friend class ShaderManager;

	private:
		GLuint idSP;
		std::vector<Shader *> shaders;
		bool linked = false;

		void compruebaErroresSP() const;

	protected:
		ShaderProgram();

		explicit ShaderProgram(std::vector<Shader *> shaders);

	public:

		ShaderProgram(const ShaderProgram &orig);

		~ShaderProgram();

		void addShader(Shader *shader);

		void activateShaderProgram();

		GLuint getIdSP() const;

	};
}


#endif //PAG_SHADERPROGRAM_H
