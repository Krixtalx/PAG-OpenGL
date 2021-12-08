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
		                                                    new Material({0.7, 0.15, 0.7}, {1, 1, 1}, {0.8, 0.8, 0.8},
		                                                                 32));
	} catch (std::runtime_error &e) {
		throw e;
	}
	modelos.resize(2);
	//creaModeloTriangulo();
	//creaModeloTetraedro();
	auto *modelo = new Modelo("DefaultSP", "../vaca.obj", {0, 0, 0}, {-90, 0, 180});
	modelo->setMaterial("DefaultMat");
	modelos.push_back(modelo);

	luces.emplace_back(glm::vec3(0.25, 0.25, 0.25));
	luces.emplace_back(glm::vec3(0, 0.3, 0), glm::vec3(0, 0.5, 0), glm::vec3(1, 1, 1), true);
	luces.emplace_back(glm::vec3(0.3, 0, 0), glm::vec3(0.5, 0, 0), glm::vec3(1, 0, 0), false);
	luces.emplace_back(glm::vec3(0, 0, 0.3), glm::vec3(0, 0, 0.5), glm::vec3(0.25, 0.25, -1), glm::vec3(0, 0, 1), 40.0f,
	                   16);

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
	glDepthFunc(GL_LEQUAL);
}

/**
 * Método para hacer el refresco de la escena
 */
void PAG::Renderer::refrescar() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 matrizMVP = camara.matrizMVP();
	glm::mat4 matrizMV = camara.matrizMV();
	for (int i = 0; i < luces.size(); i++) {
		glBlendFunc(GL_SRC_ALPHA, i == 0 ? GL_ONE_MINUS_SRC_ALPHA : GL_ONE);
		for (Modelo *modelo: modelos) {
			if (modelo)
				try {
					luces[i].aplicarLuz(modelo->getShaderProgram(), matrizMV);
					modelo->dibujarModelo(modo, matrizMVP, matrizMV);
				} catch (std::runtime_error &e) {
					throw e;
				}
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
		auto *modelo = new PAG::Modelo("DefaultSP", {0, 1, -1});
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
		auto *modelo = new PAG::Modelo("DefaultSP");
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

void PAG::Renderer::movimientoCamara(const std::string &movimiento, float mov) {
	if (movimiento == "truck") {
		camara.truck(mov);
	} else if (movimiento == "dolly") {
		camara.dolly(mov);
	} else if (movimiento == "boom") {
		camara.boom(mov);
	} else if (movimiento == "crane") {
		camara.crane(mov);
	} else if (movimiento == "zoom") {
		camara.zoom(mov);
	} else if (movimiento == "orbitX") {
		camara.orbitX(mov);
	} else if (movimiento == "orbitY") {
		camara.orbitY(mov);
	} else if (movimiento == "reset") {
		camara.reset();
	}
}
