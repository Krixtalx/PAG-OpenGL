//
// Created by Niskp on 08/10/2021.
//

#ifndef PAG_MODELO_H
#define PAG_MODELO_H


#include <GL/glew.h>
#include <vector>
#include <string>
#include "RenderOptions.h"

namespace PAG {
	class Modelo {
	private:
		GLuint idVAO{};
		std::vector<GLuint> idVBO;
		std::vector<GLuint> idIBO;
		std::vector<std::vector<GLfloat>> vbos;
		std::vector<std::vector<GLuint>> ibos;
		std::string shaderProgram;
		GLuint numVertices;

		GLenum getGLDrawMode(PAG::modoDibujado modo);


	public:
		Modelo(std::string shaderProgram, GLuint numVertices);

		Modelo(Modelo &orig);

		~Modelo();

		void nuevoVBO(PAG::paramShader tipoDato, std::vector<GLfloat> datos, GLenum freqAct);

		void nuevoIBO(PAG::modoDibujado modo, std::vector<GLuint> datos, GLenum freqAct);

		void dibujarModelo(PAG::modoDibujado modo);
	};
}


#endif //PAG_MODELO_H
