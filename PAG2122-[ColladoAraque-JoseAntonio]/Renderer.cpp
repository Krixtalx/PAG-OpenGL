//
// Created by Niskp on 15/09/2021.
//

#include "Renderer.h"


PAG::Renderer *PAG::Renderer::instancia = nullptr;

/**
 * Constructor por defecto
 */
PAG::Renderer::Renderer() {}

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
}

/**
 * Método para cambiar el color de fondo de la escena
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
