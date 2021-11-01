//
// Created by Niskp on 15/09/2021.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include "Modelo.h"
#include "Camara.h"

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

		float rojoFondo = 0.15;
		float verdeFondo = 0.15;
		float azulFondo = 0.2;

		bool triangulo = false, tetraedro = false;
		std::vector<PAG::Modelo *> modelos;

		PAG::Camara camara;

	public:
		virtual ~Renderer();

		static Renderer *getInstancia();

		void inicializaOpenGL();

		void refrescar() const;

		void setColorFondo(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

		void actualizarColorFondo() const;

		void creaModeloTriangulo();

		void creaModeloTetraedro();

		void eliminaModeloTriangulo();

		void eliminaModeloTetraedro();

		const GLubyte *getPropiedadGL(GLenum propiedad);

		void activarUtilidadGL(GLenum utility);

		void setViewport(GLint x, GLint y, GLsizei width, GLsizei height);

		void limpiarGL(GLbitfield mascara);

		float getRojoFondo() const;

		void setRojoFondo(float rojoFondo);

		float getVerdeFondo() const;

		void setVerdeFondo(float verdeFondo);

		float getAzulFondo() const;

		void setAzulFondo(float azulFondo);

		Camara &getCamara();

	};
}


#endif //RENDERER_H
