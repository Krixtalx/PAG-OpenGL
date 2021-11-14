//
// Created by Niskp on 15/09/2021.
//

#include "Renderer.h"
#include "ShaderManager.h"
#include "MaterialManager.h"
#include <stdexcept>


PAG::Renderer *PAG::Renderer::instancia = nullptr;

/**
 * Constructor por defecto
 */
PAG::Renderer::Renderer() {
	try {
		PAG::ShaderManager::getInstancia()->nuevoShader("VertexShader", GL_VERTEX_SHADER, "../pag-vs.glsl");
		PAG::ShaderManager::getInstancia()->nuevoShader("FragmentShader", GL_FRAGMENT_SHADER, "../pag-fs.glsl");
		PAG::ShaderManager::getInstancia()->nuevoShaderProgram("DefaultSP");
		PAG::ShaderManager::getInstancia()->addShaderToSP("VertexShader", "DefaultSP");
		PAG::ShaderManager::getInstancia()->addShaderToSP("FragmentShader", "DefaultSP");

		PAG::MaterialManager::getInstancia()->nuevoMaterial("DefaultMat",
		                                                    new Material({0.5, 0.2, 1}, {0, 0, 0}, {0, 0, 0}, 1));
	} catch (std::runtime_error &e) {
		throw e;
	}
	modelos.resize(2);
	creaModeloTriangulo();
	creaModeloTetraedro();
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
	activarUtilidadGL(GL_BLEND);
}

/**
 * Método para hacer el refresco de la escena
 */
void PAG::Renderer::refrescar() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 matrizMVP = camara.matrizMVP();
	for (Modelo *modelo: modelos) {
		if (modelo)
			try {
				modelo->dibujarModelo(modo, matrizMVP);
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
	camara.setAlto(height);
	camara.setAncho(width);
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
void PAG::Renderer::creaModeloTriangulo() {
	if (!triangulo) {
		auto *modelo = new PAG::Modelo("DefaultSP", 3, {-2, 0, 2});
		modelo->cargaModeloTriangulo();
		modelos[0] = modelo;
		triangulo = true;
	}
}

/**
 * Método encargado de crear un modelo. Actualmente solo crea un tetraedro.
 */
void PAG::Renderer::creaModeloTetraedro() {
	if (!tetraedro) {
		auto *modelo = new PAG::Modelo("DefaultSP", 4);
		modelo->cargaModeloTetraedro();
		modelos[1] = modelo;
		tetraedro = true;
	}
}

void PAG::Renderer::eliminaModeloTriangulo() {
	if (triangulo) {
		delete modelos[0];
		modelos[0] = 0;
		triangulo = false;
	}
}

void PAG::Renderer::eliminaModeloTetraedro() {
	if (tetraedro) {
		delete modelos[1];
		modelos[1] = 0;
		tetraedro = false;
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

PAG::Camara &PAG::Renderer::getCamara() {
	return camara;
}

void PAG::Renderer::setModo(PAG::modoDibujado modo) {
	Renderer::modo = modo;
}
