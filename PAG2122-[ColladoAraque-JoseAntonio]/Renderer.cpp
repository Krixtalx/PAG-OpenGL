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
	for (auto modelo: modelos) {
		delete modelo;
	}
}

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
	activarUtilidadGL(GL_DEBUG_OUTPUT);
}

/**
 * Método para hacer el refresco de la escena
 */
void PAG::Renderer::refrescar() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (auto modelo: modelos) {
		try {
			modelo->dibujarModelo(PAG::mallaTriangulos);
		} catch (std::runtime_error &e) {
			throw e;
		}
	}
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
	if (modelos.empty()) {
		std::vector<glm::vec3> vertices = {{-.5, -.5, 0},
		                                   {.5,  -.5, 0},
		                                   {.0,  .5,  0}};
		std::vector<glm::vec3> localColores = {{1, 0, 0},
		                                       {0, 1, 0},
		                                       {0, 0, 1}};
		std::vector<GLuint> indices = {0, 1, 2};

		auto *modelo = new PAG::Modelo("DefaultSP", 3);
		modelo->nuevoVBO(PAG::posicion, vertices, GL_STATIC_DRAW);
		modelo->nuevoVBO(PAG::color, localColores, GL_STATIC_DRAW);
		modelo->nuevoIBO(PAG::mallaTriangulos, indices, GL_STATIC_DRAW);
		modelos.push_back(modelo);
	}
}

void PAG::Renderer::eliminaModelo() {
	if (!modelos.empty()) {
		delete modelos[modelos.size() - 1];
		modelos.pop_back();
	}
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