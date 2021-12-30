//
// Created by Niskp on 15/09/2021.
//

#include "Renderer.h"
#include "ShaderManager.h"
#include "MaterialManager.h"
#include "ModeloRevolucion.h"
#include <stdexcept>
#include <glm/gtx/transform.hpp>


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

		PAG::ShaderManager::getInstancia()->nuevoShader("VertexShaderMS", GL_VERTEX_SHADER, "../pag-vs-ms.glsl");
		PAG::ShaderManager::getInstancia()->nuevoShader("FragmentShaderMS", GL_FRAGMENT_SHADER, "../pag-fs-ms.glsl");
		PAG::ShaderManager::getInstancia()->nuevoShaderProgram("MapaSombrasSP");
		PAG::ShaderManager::getInstancia()->addShaderToSP("VertexShaderMS", "MapaSombrasSP");
		PAG::ShaderManager::getInstancia()->addShaderToSP("FragmentShaderMS", "MapaSombrasSP");

		PAG::MaterialManager::getInstancia()->nuevoMaterial("DefaultMat",
		                                                    new Material({0.7, 0.15, 0.7}, {1, 1, 1}, {0.8, 0.8, 0.8},
		                                                                 32));
		PAG::MaterialManager::getInstancia()->nuevoMaterial("Vaca",
		                                                    new Material({0.7, 0.15, 0.7}, {1, 1, 1}, {0.8, 0.8, 0.8},
		                                                                 32, "../spot_texture.png"));
		PAG::MaterialManager::getInstancia()->nuevoMaterial("Dado",
		                                                    new Material({0.7, 0.15, 0.7}, {1, 1, 1}, {0.8, 0.8, 0.8},
		                                                                 32, "../dado.png", "../NormalMap.png"));

		PAG::MaterialManager::getInstancia()->nuevoMaterial("Cilindro1",
		                                                    new Material({0.25, 0.25, 0.25}, {0.4, 0.4, 0.4},
		                                                                 {0.774597, 0.774597, 0.774597},
		                                                                 76, "../Metal_Plate_015_basecolor.png",
		                                                                 "../Metal_Plate_015_normal.png"));

		PAG::MaterialManager::getInstancia()->nuevoMaterial("Cilindro2",
		                                                    new Material({0.25, 0.25, 0.25}, {0.4, 0.4, 0.4},
		                                                                 {0.774597, 0.774597, 0.774597},
		                                                                 76, "../Sci_fi_Metal_Panel_002_basecolor.png",
		                                                                 "../Sci_fi_Metal_Panel_002_normal.png"));

	} catch (std::runtime_error &e) {
		throw e;
	}

	auto *modelo = new Modelo("DefaultSP", "../vaca.obj", {0, 0, 0}, {-90, 0, 180}, {1, 1, 1});
	modelo->setMaterial("Vaca");
	modelos.push_back(modelo);

	modelo = new Modelo("DefaultSP", "../dado.obj", {0, 1, -1}, {0, 0, 0});
	modelo->setMaterial("Dado");
	modelos.push_back(modelo);

	creaModeloTetraedro();

	modelo = new ModeloRevolucion("DefaultSP");
	modelo->setMaterial("Cilindro2");
	modelos.push_back(modelo);

	creaModeloTriangulo();

	luces.emplace_back(glm::vec3(0.45, 0.45, 0.45));
	luces.emplace_back(glm::vec3(0, 0.5, 0), glm::vec3(0, 0.8, 0), glm::vec3(2, 2, 2), true);
	luces.emplace_back(glm::vec3(0.45, 0, 0), glm::vec3(0.8, 0, 0), glm::vec3(1, 0, 0), false);
	luces.emplace_back(glm::vec3(0, 0, 0.75), glm::vec3(0, 0, 1), glm::vec3(0, 0.5, -3), glm::vec3(0, 0, 1),
	                   40.0f, 64);
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
	activarUtilidadGL(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFF);
	glDepthFunc(GL_LEQUAL);
	glGenFramebuffers(1, &fboSombras);
	glFrontFace(GL_CCW);
}

/**
 * Método para hacer el refresco de la escena
 */
void PAG::Renderer::refrescar() {
	//Shadowmap
	if (actualizarSombras) {
		for (const auto &luz: luces) {
			if (luz.emiteSombras()) {
				GLuint idMapaSombras = luz.getIdMapaSombras();
				glBindFramebuffer(GL_FRAMEBUFFER, fboSombras);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
				                       idMapaSombras, 0);
				glReadBuffer(GL_NONE); // NO necesitamos información de color; sólo la
				glDrawBuffer(GL_NONE); // profundidad
				GLenum estado = glCheckFramebufferStatus(GL_FRAMEBUFFER);
				if (estado != GL_FRAMEBUFFER_COMPLETE) {
					throw std::runtime_error(
							"[Renderer::refrescar]: Se ha intentado usar fboSombras antes de que este listo -> " +
							std::to_string(estado));
				}

				glActiveTexture(GL_TEXTURE2); // Activamos unidad de textura
				glBindTexture(GL_TEXTURE_2D, idMapaSombras); // Asociamos la textura del FBO

				// Sólo borramos profundidad. Ignoramos color
				glClear(GL_DEPTH_BUFFER_BIT);
				glViewport(0, 0, PAG::anchoMS, PAG::altoMS);
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LESS);

				// Para evitar el “shadow acne”, eliminamos caras delanteras
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);

				glm::mat4 matrizVP = luz.generarMatrizVPMS();

				for (Modelo *modelo: modelos) {
					if (modelo)
						try {
							glm::mat4 matrizMVP = matrizVP * modelo->getMModelado();
							PAG::ShaderManager::getInstancia()->activarSP("MapaSombrasSP");
							PAG::ShaderManager::getInstancia()->setUniform("MapaSombrasSP", "matrizModVisProy",
							                                               matrizMVP);
							modelo->dibujarModeloParaSombras();
						} catch (std::runtime_error &e) {
							throw e;
						}
				}
			}
		}
		actualizarSombras = false;

		//Lo dejamos como estaba antes
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, PAG::anchoVentanaPorDefecto, PAG::altoVentanaPorDefecto);
		glDepthFunc(GL_LEQUAL);
		glCullFace(GL_BACK);
		//glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}

	//Multipasada con luces
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 matrizMVP = camara.matrizMVP();
	glm::mat4 matrizMV = camara.matrizMV();
	for (int i = 0; i < luces.size(); i++) {
		glBlendFunc(GL_SRC_ALPHA, i == 0 ? GL_ONE_MINUS_SRC_ALPHA : GL_ONE);
		for (Modelo *modelo: modelos) {
			if (modelo)
				try {
					auto matrizMS = glm::scale(glm::vec3(.5, .5, .5));
					matrizMS[3][0] = matrizMS[3][1] = matrizMS[3][2] = 0.5;

					if (luces[i].emiteSombras())
						matrizMS *= luces[i].generarMatrizVPMS();

					if (modelo->getModo() != PAG::wireframe)
						luces[i].aplicarLuz(modelo->getShaderProgram(), matrizMV);

					modelo->dibujarModelo(matrizMVP, matrizMV, matrizMS, luces[i].getTipoLuz());
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
	PAG::anchoVentanaPorDefecto = width;
	PAG::altoVentanaPorDefecto = height;
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
	auto *modelo = new PAG::Modelo("DefaultSP", "NULL", {-1, 1, -1}, {0, 0, 0});
	modelo->cargaModeloTriangulo();
	modelo->setMaterial("DefaultMat");
	modelos.push_back(modelo);

}

/**
 * Método encargado de crear un modelo. Actualmente solo crea un tetraedro.
 */
void PAG::Renderer::creaModeloTetraedro() {
	auto *modelo = new PAG::Modelo("DefaultSP", "NULL", {-1.5f, -0.2f, -0.5f}, {0, 0, 0});
	modelo->cargaModeloTetraedro();
	modelo->setMaterial("DefaultMat");
	modelos.push_back(modelo);
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

void PAG::Renderer::cambiarModoDibujado() {
	modelos[modeloActivo]->cambiarModoDibujado();
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

unsigned PAG::Renderer::cambiarModeloActivo() {
	modeloActivo = ++modeloActivo % modelos.size();
	return modeloActivo;
}

void PAG::Renderer::cambiarModoTextura() {
	modelos[modeloActivo]->cambiarUsoTextura();
}

void PAG::Renderer::cambiarVisibilidad() {
	modelos[modeloActivo]->cambiarVisibilidad();
	actualizarSombras = true;
}

void PAG::Renderer::cambiarNormalMap() {
	modelos[modeloActivo]->cambiarUsoNormalMap();
}
