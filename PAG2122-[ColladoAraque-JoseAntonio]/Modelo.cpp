//
// Created by Niskp on 08/10/2021.
//

#include "Modelo.h"
#include "RenderOptions.h"
#include "ShaderManager.h"

#include <utility>
#include <stdexcept>
#include <climits>

/**
 * Constructor parametrizado
 * @param shaderProgram que se usará para renderizar el modelo
 * @param numVertices que contiene el modelo
 */
PAG::Modelo::Modelo(std::string shaderProgram, GLuint numVertices) : numVertices(numVertices),
                                                                     shaderProgram(std::move(shaderProgram)) {
	//Creamos nuestro VAO
	glGenVertexArrays(1, &idVAO);
	glBindVertexArray(idVAO);

	//Ponemos tanto espacios en el vector de VBO como parametros tengamos para el shader.
	idVBO.resize(PAG::numParamShader());
	vbos.resize(PAG::numParamShader());
	for (unsigned int &i: idVBO) {
		i = UINT_MAX;
	}
	//Ponemos tanto espacios en el vector de IBO como modos de dibujado tengamos.
	idIBO.resize(PAG::numModosDibujo());
	ibos.resize(PAG::numModosDibujo());
	for (unsigned int &i: idIBO) {
		i = UINT_MAX;
	}
}

/**
 * Constructor copia. Copia el numVertices y el shaderProgram y realiza una nueva instanciacion de los vbos e ibos
 * @param orig
 */
PAG::Modelo::Modelo(PAG::Modelo &orig) : numVertices(orig.numVertices), shaderProgram(orig.shaderProgram),
                                         vbos(orig.vbos), ibos(orig.ibos) {
	//Creamos nuestro VAO
	glGenVertexArrays(1, &idVAO);
	glBindVertexArray(idVAO);

	//Ponemos tanto espacios en el vector de VBO como parametros tengamos para el shader.
	idVBO.resize(PAG::numParamShader());
	//Ponemos tanto espacios en el vector de IBO como modos de dibujado tengamos.
	idIBO.resize(PAG::numModosDibujo());

	for (int i = 0; i < vbos.size(); ++i) {
		nuevoVBO(static_cast<paramShader>(i), vbos[i], GL_STATIC_DRAW);
	}
	for (int i = 0; i < ibos.size(); ++i) {
		nuevoIBO(static_cast<modoDibujado>(i), ibos[i], GL_STATIC_DRAW);
	}
}

/**
 * Destructor. Libera todos los recursos reservados a OpenGL.
 */
PAG::Modelo::~Modelo() {
	for (unsigned int &vbo: idVBO) {
		if (vbo != UINT_MAX)
			glDeleteBuffers(1, &vbo);
	}
	for (unsigned int &ibo: idIBO) {
		if (ibo != UINT_MAX)
			glDeleteBuffers(1, &ibo);
	}
	glDeleteVertexArrays(1, &idVAO);
}

/**
 * Instancia un VBO en el contexto OpenGL y lo guarda en vbos
 * @param tipoDato parametro del shader que representa el vbo
 * @param datos a instanciar
 * @param freqAct GLenum que indica con que frecuencia se van a modificar los vertices. GL_STATIC_DRAW siempre por ahora
 */
void PAG::Modelo::nuevoVBO(PAG::paramShader tipoDato, std::vector<glm::vec3> datos, GLenum freqAct) {
	//Si hay un buffer de este tipo instanciado, lo eliminamos
	if (idVBO[tipoDato] != UINT_MAX) {
		glDeleteBuffers(1, &idVBO[tipoDato]);
	}
	vbos[tipoDato] = datos;
	glBindVertexArray(idVAO);
	glGenBuffers(1, &idVBO[tipoDato]);
	glBindBuffer(GL_ARRAY_BUFFER, idVBO[tipoDato]);
	glBufferData(GL_ARRAY_BUFFER, datos.size() * sizeof(glm::vec3), datos.data(), freqAct);
	glVertexAttribPointer(tipoDato, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
	                      nullptr);
	glEnableVertexAttribArray(tipoDato);
}

/**
 * Instancia un IBO en el contexto OpenGL y lo guarda en ibos
 * @param modo modo de dibujado que representa el ibo
 * @param datos a instanciar
 * @param freqAct GLenum que indica con que frecuencia se van a modificar los vertices. GL_STATIC_DRAW siempre por ahora
 */
void PAG::Modelo::nuevoIBO(PAG::modoDibujado modo, std::vector<GLuint> datos, GLenum freqAct) {
	//Si hay un buffer de este tipo instanciado, lo eliminamos
	if (idIBO[modo] != UINT_MAX) {
		glDeleteBuffers(1, &idIBO[modo]);
	}
	ibos[modo] = datos;
	glBindVertexArray(idVAO);
	glGenBuffers(1, &idIBO[modo]);
	glBindBuffer(GL_ARRAY_BUFFER, idIBO[modo]);
	glBufferData(GL_ARRAY_BUFFER, datos.size() * sizeof(GLuint), datos.data(), freqAct);
}

/**
 * Función a la que se llama cuando se debe de dibujar el modelo
 * @param modo modo de dibujado a usar
 */
void PAG::Modelo::dibujarModelo(PAG::modoDibujado modo, glm::mat4 matrizMVP) {
	try {
		PAG::ShaderManager::getInstancia()->activarSP(shaderProgram);
		PAG::ShaderManager::getInstancia()->setUniform(this->shaderProgram, "matrizMVP", matrizMVP);
		glBindVertexArray(idVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO[modo]);
		glDrawElements(getGLDrawMode(modo), numVertices, GL_UNSIGNED_INT, nullptr);
	} catch (std::runtime_error &e) {
		throw e;
	}
}

/**
 * Crea el modelo de un triangulo
 */
void PAG::Modelo::cargaModeloTriangulo() {
	std::vector<glm::vec3> vertices = {{-.5, -.5, 0},
	                                   {.5,  -.5, 0},
	                                   {.0,  .5,  0}};
	std::vector<glm::vec3> localColores = {{1, 0, 0},
	                                       {0, 1, 0},
	                                       {0, 0, 1}};
	std::vector<GLuint> indices = {0, 1, 2};

	this->nuevoVBO(PAG::posicion, vertices, GL_STATIC_DRAW);
	this->nuevoVBO(PAG::color, localColores, GL_STATIC_DRAW);
	this->nuevoIBO(PAG::mallaTriangulos, indices, GL_STATIC_DRAW);
}

/**
 * Traduce de modoDibujado a los modos de dibujado de OpenGL
 * @param modo de modoDibujado
 * @return GLenum que indica como debe de dibujarse
 */
GLenum PAG::Modelo::getGLDrawMode(PAG::modoDibujado modo) {
	switch (modo) {
		case PAG::nubePuntos:
			return GL_POINTS;
			break;
		case PAG::wireframe:
			return GL_LINES;
			break;
		default:
			return GL_TRIANGLES;
			break;
	}
}
