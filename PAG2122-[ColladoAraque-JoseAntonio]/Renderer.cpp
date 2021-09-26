//
// Created by Niskp on 15/09/2021.
//

#include "Renderer.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>


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
 * Método que actualiza el color de fondo de la escena al indicado por los atributos
 */
void PAG::Renderer::actualizarColorFondo() {
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
 * --------------------------------SHADERS-------------------------------------------
 */


/**
 * Método encargado de crear un Shader program
 */
void PAG::Renderer::creaShaderProgram() {
	try {
		cargaShader(GL_VERTEX_SHADER, "../pag03-vs.glsl");
		cargaShader(GL_FRAGMENT_SHADER, "../pag03-fs.glsl");
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}

	idSP = glCreateProgram();
	glAttachShader(idSP, idVS);
	glAttachShader(idSP, idFS);
	glLinkProgram(idSP);

}

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
	                             .5, -.5, 0,
	                             .0, .5, 0,
	                             1, 0, 0,
	                             0, 1, 0,
	                             0, 0, 1};
	GLuint indices[] = {0, 1, 2};

	//Creamos nuestro VAO
	glGenVertexArrays(1, &idVAO);
	glBindVertexArray(idVAO);

	//Creamos el primer VBO para los vertices del triángulo
	glGenBuffers(1, &idVBO);
	glBindBuffer(GL_ARRAY_BUFFER, idVBO);
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

	glGenBuffers(1, &idIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices,
	             GL_STATIC_DRAW);
}


/**
 * Comprueba si ha ocurrido algún error en la compilación del shader
 * @param idShader a comprobar
 * @throw runtime_error en caso de que se encuentre algún error
 */
void PAG::Renderer::comprobarErroresShader(GLuint idShader) {
	GLint resultadoCompilacion;
	glGetShaderiv(idShader, GL_COMPILE_STATUS, &resultadoCompilacion);

	if (resultadoCompilacion == GL_FALSE) {
		// Ha habido un error en la compilación.
		// Para saber qué ha pasado, tenemos que recuperar el mensaje de error de OpenGL
		GLint tamMsj = 0;
		std::string mensaje;
		glGetShaderiv(idShader, GL_INFO_LOG_LENGTH, &tamMsj);
		if (tamMsj > 0) {
			auto *mensajeFormatoC = new GLchar[tamMsj];
			GLint datosEscritos = 0;
			glGetShaderInfoLog(idShader, tamMsj, &datosEscritos, mensajeFormatoC);
			mensaje.assign(mensajeFormatoC);
			delete[] mensajeFormatoC;
			throw std::runtime_error(mensaje);
		}
	}
}

/**
 *
 * @param shaderType
 * @param ruta
 */
void PAG::Renderer::cargaShader(GLenum shaderType, const std::string &ruta) {
	GLuint idShader;

	idShader = glCreateShader(shaderType);
	if (shaderType == GL_VERTEX_SHADER)
		idVS = idShader;
	else if (shaderType == GL_FRAGMENT_SHADER)
		idFS = idShader;

	if (idShader == 0) {
		// Ha ocurrido un error al intentar crear el shader
		throw std::runtime_error("Error desconocido al intentar crear el shader.");
	}

	std::ifstream archivoShader;
	archivoShader.open(ruta, std::ifstream::in);

	if (!archivoShader.is_open()) {
		// Error abriendo el archivo
		throw std::runtime_error("Ha ocurrido un error al intentar abrir el fichero " + ruta);
	}

	std::stringstream streamShader;
	streamShader << archivoShader.rdbuf();
	std::string codigoFuenteShader = streamShader.str();

	archivoShader.close();

	const GLchar *codigoFuenteFormatoC = codigoFuenteShader.c_str();
	glShaderSource(idShader, 1, &codigoFuenteFormatoC, nullptr);
	glCompileShader(idShader);

	try {
		comprobarErroresShader(idShader);
	} catch (std::runtime_error &e) {
		throw e;
	}
}


/**
 * ------------------- Getters y Setters ------------------------------------
 */

float PAG::Renderer::getRojoFondo() const {
	return rojoFondo;
}

void PAG::Renderer::setRojoFondo(float rojoFondo) {
	Renderer::rojoFondo = rojoFondo;
}

float PAG::Renderer::getVerdeFondo() const {
	return verdeFondo;
}

void PAG::Renderer::setVerdeFondo(float verdeFondo) {
	Renderer::verdeFondo = verdeFondo;
}

float PAG::Renderer::getAzulFondo() const {
	return azulFondo;
}

void PAG::Renderer::setAzulFondo(float azulFondo) {
	Renderer::azulFondo = azulFondo;
}

