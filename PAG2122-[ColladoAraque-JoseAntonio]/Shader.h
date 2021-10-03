//
// Created by Niskp on 01/10/2021.
//

#ifndef PAG_SHADER_H
#define PAG_SHADER_H


#include <GL/glew.h>
#include <string>

namespace PAG {
	class Shader {
	private:
		const std::string nombreShader;
		GLuint idShader;
		GLenum tipoShader;

		void cargaShader(const std::string &ruta) const;

		void compilaShader();

		void compruebaErroresShader() const;

	public:
		Shader(const std::string &nombreShader, GLenum tipoShader, const std::string &ruta);

		GLuint getShaderId() const;

		GLenum getTipoShader() const;
	};
}


#endif //PAG_SHADER_H
