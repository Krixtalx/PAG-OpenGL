//
// Created by Niskp on 08/10/2021.
//

#ifndef PAG_MODELO_H
#define PAG_MODELO_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <assimp/scene.h>
#include "RenderOptions.h"

namespace PAG {
	class Modelo {
	private:
		GLuint idVAO{};
		std::vector<GLuint> idVBO;
		std::vector<GLuint> idIBO;
		std::vector<std::vector<glm::vec3>> vbos;
		std::vector<glm::vec2> textura;
		std::vector<std::vector<GLuint>> ibos;
		std::string shaderProgram;
		std::string material;
		glm::mat4 mModelado{};
		PAG::modoDibujado modo = PAG::mallaTriangulos;
		bool usarTexturas = true;
		bool visible = true;

		GLenum getGLDrawMode(PAG::modoDibujado modo);

		void cargaModelo(const std::string &path);

		void procesarNodo(aiNode *node, const aiScene *scene);

		void procesarMalla(aiMesh *mesh, const aiScene *scene);

	public:

		Modelo(std::string shaderProgram, const std::string &path = "NULL", glm::vec3 pos = {0, 0, 0},
		       glm::vec3 rot = {0, 0, 0});

		Modelo(Modelo &orig);

		~Modelo();

		void nuevoVBO(PAG::paramShader tipoDato, const std::vector<glm::vec3> &datos, GLenum freqAct);

		void nuevoVBO(PAG::paramShader tipoDato, const std::vector<glm::vec2> &datos, GLenum freqAct);

		void nuevoIBO(PAG::modoDibujado modo, const std::vector<GLuint> &datos, GLenum freqAct);

		void setMaterial(const std::string &material);

		void dibujarModelo(glm::mat4 matrizMVP, glm::mat4 matrizMV, PAG::tipoLuz tipoLuz);

		void cargaModeloTriangulo();

		void cargaModeloTetraedro();

		const std::string &getShaderProgram() const;

		void cambiarModoDibujado();

		void cambiarUsoTextura();

		void cambiarVisibilidad();

		PAG::modoDibujado getModo() const;
	};
}


#endif //PAG_MODELO_H
