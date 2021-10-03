//
// Created by Niskp on 15/09/2021.
//

#include "Renderer.h"
#include "ShaderManager.h"
#include <stdexcept>


PAG::Renderer *PAG::Renderer::instancia = nullptr;

/**
 * Constructor por defecto
 */
PAG::Renderer::Renderer() {
	try {
		PAG::ShaderManager::getInstancia()->nuevoShader("VertexShader", GL_VERTEX_SHADER, "../pag03-vs.glsl");
		PAG::ShaderManager::getInstancia()->nuevoShader("FragmentShader", GL_FRAGMENT_SHADER, "../pag03-fs.glsl");
		PAG::ShaderManager::getInstancia()->nuevoShaderProgram("DefaultSP");
		PAG::ShaderManager::getInstancia()->addShaderToSP("VertexShader", "DefaultSP");
		PAG::ShaderManager::getInstancia()->addShaderToSP("FragmentShader", "DefaultSP");
	} catch (std::runtime_error &e) {
		throw e;
	}
	creaModelo();
}

/**
 * Destructor
 */
PAG::Renderer::~Renderer() {
	glDeleteBuffers(1, &idIBO);
	glDeleteBuffers(1, &idVBO);
	glDeleteBuffers(1, &idVBO2);

	glDeleteVertexArrays(1, &idVAO);
};

/**
 * Consulta del objeto único de la clase
 * @return Puntero al Renderer
 */
PAG::Renderer *PAG::Renderer::getInstancia() {
	if (!instancia) {
		try {
			instancia = new Renderer;
		} catch (std::runtime_error &e) {
			throw e;
		}
	}
	return instancia;
}

/**
 * Inicializa los parámetros globales de OpenGL.
 * Establece un color de fondo inicial
 * Activa el ZBuffer.
 * Activa el Antialiasing MultiSampling (MSAA)
 */
void PAG::Renderer::inicializaOpenGL() {

	glClearColor(rojoFondo, verdeFondo, azulFondo, 1);
	activarUtilidadGL(GL_DEPTH_TEST);
	activarUtilidadGL(GL_MULTISAMPLE);
}

/**
 * Método para hacer el refresco de la escena
 */
void PAG::Renderer::refrescar() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	PAG::ShaderManager::getInstancia()->activarSP("DefaultSP");
	glBindVertexArray(idVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

}

/**
 * Método para cambiar el colorSeleccionado de fondo de la escena
 * @param red
 * @param green
 * @param blue
 * @param alpha
 */
void PAG::Renderer::setColorFondo(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
	rojoFondo = red;
	verdeFondo = green;
	azulFondo = blue;
	glClearColor(red, green, blue, alpha);
}

/**
 * Método que actualiza el color de fondo de la escena al indicado por los atributos
 */
void PAG::Renderer::actualizarColorFondo() const {
	glClearColor(rojoFondo, verdeFondo, azulFondo, 1);
}

/**
 * Método que nos permite obtener las propiedades del contexto OpenGL construido
 * @param propiedad a obtener
 * @return GLubyte con la propiedad requerida
 */
const GLubyte *PAG::Renderer::getPropiedadGL(GLenum propiedad) {
	return glGetString(propiedad);
}

/**
 * Activa la utilidad de OpenGL indicada
 * @param utility
 */
void PAG::Renderer::activarUtilidadGL(GLenum utility) {
	glEnable(utility);
}

/**
 * Cambia el tamaño del viewport al indicado
 * @param x punto de referencia
 * @param y punto de referencia
 * @param width ancho de la ventana
 * @param height alto de la ventana
 */
void PAG::Renderer::setViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
	glViewport(x, y, width, height);
}

/**
 * Limpia el buffer OpenGL indicado en la mascara
 * @param mascara
 */
void PAG::Renderer::limpiarGL(GLbitfield mascara) {
	glClear(mascara);
}


/**
 * --------------------------------Modelo-------------------------------------------
 */

/**
 * Método encargado de crear un modelo. Actualmente solo crea un triangulo.
 */
void PAG::Renderer::creaModelo() {
	GLfloat vertices[] = {-.5, -.5, 0,
	                      .5, -.5, 0,
	                      .0, .5, 0};
	GLfloat localColores[] = {1, 0, 0,
	                          0, 1, 0,
	                          0, 0, 1};

	//Para VBOs entrelazados
	GLfloat verticesColores[] = {-.5, -.5, 0,
	                             1, 0, 0,
	                             .5, -.5, 0,
	                             0, 1, 0,
	                             .0, .5, 0,
	                             0, 0, 1};
	GLuint indices[] = {0, 1, 2};

	//Creamos nuestro VAO
	glGenVertexArrays(1, &idVAO);
	glBindVertexArray(idVAO);

	//Versión no entrelazada
	//Creamos el primer VBO para los vertices del triángulo
	glGenBuffers(1, &idVBO);
	glBindBuffer(GL_ARRAY_BUFFER, idVBO);
	if (!entrelazado) {
		//Versión no entrelazada
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices,
		             GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
		                      nullptr);
		glEnableVertexAttribArray(0);

		//Creamos el segundo VBO para los colores del triángulo
		glGenBuffers(1, &idVBO2);
		glBindBuffer(GL_ARRAY_BUFFER, idVBO2);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), localColores,
		             GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
		                      nullptr);
		glEnableVertexAttribArray(1);
	} else {
		//Versión entrelazada
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), verticesColores,
		             GL_STATIC_DRAW);
		//Especificamos como acceder al atributo 0 (posición)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
		                      nullptr);
		glEnableVertexAttribArray(0);

		//Especificamos como acceder al atributo 1 (Color)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
		                      (GLubyte *) (3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

	}

	glGenBuffers(1, &idIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices,
	             GL_STATIC_DRAW);
}


/**
 * ------------------- Getters y Setters ------------------------------------
 */

float PAG::Renderer::getRojoFondo() const {
	return rojoFondo;
}

void PAG::Renderer::setRojoFondo(float rojoFondo) {
	this->rojoFondo = rojoFondo;
}

float PAG::Renderer::getVerdeFondo() const {
	return verdeFondo;
}

void PAG::Renderer::setVerdeFondo(float verdeFondo) {
	this->verdeFondo = verdeFondo;
}

float PAG::Renderer::getAzulFondo() const {
	return azulFondo;
}

void PAG::Renderer::setAzulFondo(float azulFondo) {
	this->azulFondo = azulFondo;
}

