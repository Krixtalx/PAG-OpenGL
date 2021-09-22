//
// Created by Niskp on 15/09/2021.
//

#include "Renderer.h"


PAG::Renderer *PAG::Renderer::instancia = nullptr;

/**
 * Constructor por defecto
 */
PAG::Renderer::Renderer() {
	creaShaderProgram();
	creaModelo();
}

/**
 * Destructor
 */
PAG::Renderer::~Renderer() {}

/**
 * Consulta del objeto único de la clase
 * @return La dirección de memoria del objeto
 */
PAG::Renderer *PAG::Renderer::getInstancia() {
	if (!instancia) {
		instancia = new Renderer;
	}
	return instancia;
}

/**
 * Método para hacer el refresco de la escena
 */
void PAG::Renderer::refrescar() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUseProgram(idSP);
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
	glClearColor(red, green, blue, alpha);
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
 * Método encargado de crear un Shader program
 */
void PAG::Renderer::creaShaderProgram() {
	std::string miVertexShader =
			"#version 410\n"
			"layout (location = 0) in vec3 posicion;\n"
			"void main ()\n"
			"{\n"
			" gl_Position = vec4 ( posicion, 1 );\n"
			"}\n";
	std::string miFragmentShader =
			"#version 410\n"
			"out vec4 colorFragmento;\n"
			"void main ()\n"
			"{\n"
			" colorFragmento = vec4 ( 1.0, .4, .2, 1.0 );\n"
			"}\n";
	idVS = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *fuenteVS = miVertexShader.c_str();
	glShaderSource(idVS, 1, &fuenteVS, nullptr);
	glCompileShader(idVS);
	idFS = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fuenteFS = miFragmentShader.c_str();
	glShaderSource(idFS, 1, &fuenteFS, nullptr);
	glCompileShader(idFS);
	idSP = glCreateProgram();
	glAttachShader(idSP, idVS);
	glAttachShader(idSP, idFS);
	glLinkProgram(idSP);

}

void PAG::Renderer::creaModelo() {
	GLfloat vertices[] = {-.5, -.5, 0,
	                      .5, -.5, 0,
	                      .0, .5, 0};
	GLuint indices[] = {0, 1, 2};
	glGenVertexArrays(1, &idVAO);
	glBindVertexArray(idVAO);
	glGenBuffers(1, &idVBO);
	glBindBuffer(GL_ARRAY_BUFFER, idVBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices,
	             GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
	                      nullptr);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &idIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices,
	             GL_STATIC_DRAW);
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
