//
// Created by Niskp on 08/10/2021.
//

#ifndef PAG_MODELO_H
#define PAG_MODELO_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "RenderOptions.h"

namespace PAG {
	class Modelo {
	private:
		GLuint idVAO{};
		std::vector<GLuint> idVBO;
		std::vector<GLuint> idIBO;
		std::vector<std::vector<glm::vec3>> vbos;
		std::vector<std::vector<GLuint>> ibos;
		std::string shaderProgram;
		std::string material;
		glm::vec3 posicion;
		GLuint numVertices;

		GLenum getGLDrawMode(PAG::modoDibujado modo);

	public:
		Modelo(std::string shaderProgram, GLuint numVertices, glm::vec3 pos = {0, 0, 0});

		Modelo(Modelo &orig);

		~Modelo();

		void nuevoVBO(PAG::paramShader tipoDato, std::vector<glm::vec3> datos, GLenum freqAct);

		void nuevoIBO(PAG::modoDibujado modo, std::vector<GLuint> datos, GLenum freqAct);

		void setMaterial(const std::string &material);

		void dibujarModelo(PAG::modoDibujado modo, glm::mat4 matrizMVP);

		void cargaModeloTriangulo();

		void cargaModeloTetraedro();
	};
}


#endif //PAG_MODELO_H
