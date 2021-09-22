//
// Created by Niskp on 15/09/2021.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <gl/glew.h>
#include <xstring>

namespace PAG {
    /**
     * @brief Clase encargada de encapsular la gestión del área de dibujo
     * OpenGL
     *
     * Esta clase coordina el renderizado de las escenas OpenGL. Se implementa
     * aplicando el patrón de diseño Singleton. Está pensada para que las
     * funciones callback hagan llamadas a sus métodos
     */

    class Renderer {
    private:
	    static Renderer *instancia; ///< Puntero al único objeto de la clase
	    Renderer();

	    GLuint idVS = 0; // Identificador del vertex shader
	    GLuint idFS = 0; // Identificador del fragment shader
	    GLuint idSP = 0; // Identificador del shader program
	    GLuint idVAO = 0; // Identificador del vertex array object
	    GLuint idVBO = 0; // Identificador del vertex buffer object
	    GLuint idIBO = 0; // Identificador del index buffer object

    public:

	    float rojoFondo = 0.6;
	    float verdeFondo = 0.6;
	    float azulFondo = 0.6;
	    int colorSeleccionado = 0;
	    std::string colores[3] = {"Rojo", "Verde", "Azul"};

	    virtual ~Renderer();

	    static Renderer *getInstancia();

		void inicializaOpenGL();

	    void refrescar();

	    void setColorFondo(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

	    const GLubyte *getPropiedadGL(GLenum propiedad);

	    void activarUtilidadGL(GLenum utility);

        void setViewport(GLint x, GLint y, GLsizei width, GLsizei height);

        void limpiarGL(GLbitfield mascara);

		void creaShaderProgram();

		void creaModelo();

    };
}


#endif //RENDERER_H
