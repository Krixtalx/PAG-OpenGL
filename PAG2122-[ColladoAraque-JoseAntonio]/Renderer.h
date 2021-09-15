//
// Created by Niskp on 15/09/2021.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <xstring>
#include <gl/glew.h>

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

    public:
        virtual ~Renderer();

        static Renderer *getInstancia();

        void refrescar();

        void setColorFondo(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

        const GLubyte* getPropiedadGL(GLenum propiedad);

        void activarUtilidadGL(GLenum utility);

        void setViewport(GLint x, GLint y, GLsizei width, GLsizei height);

        void limpiarGL(GLbitfield mascara);
    };
}


#endif //RENDERER_H
