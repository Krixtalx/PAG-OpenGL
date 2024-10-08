//
// Created by Niskp on 18/10/2021.
//

#ifndef PAG_CAMARA_H
#define PAG_CAMARA_H

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace PAG {
	class Camara {
	private:
		//Parámetros intrínsecos de la camara
		glm::vec3 posicion;
		glm::vec3 puntoMira;
		glm::vec3 up;

		//Ejes locales
		glm::vec3 u;
		glm::vec3 v;
		glm::vec3 n;

		//Planos de clipping
		GLfloat zNear;
		GLfloat zFar;

		//Campo de vision de la cámara
		GLfloat fovX;
		GLfloat fovY;

		//Dimensiones del viewport
		GLuint alto;
		GLuint ancho;

		void calcularEjes();

		void calcularFovY();

	public:
		Camara();

		Camara(const glm::vec3 &posicion, const glm::vec3 &puntoMira, const glm::vec3 &up, GLfloat zNear, GLfloat zFar,
		       GLfloat fovX, GLuint alto, GLuint ancho);

		void truck(float mov);

		void dolly(float mov);

		void boom(float mov);

		void crane(float mov);

		void zoom(float angulo);

		void pan(float mov);

		void tilt(float mov);

		void orbitX(float mov);

		void orbitY(float mov);

		void reset();

		glm::mat4 matrizMVP() const;

		glm::mat4 matrizMV() const;

		GLfloat aspecto() const;

		void setAlto(GLuint alto);

		void setAncho(GLuint ancho);
	};
}


#endif //PAG_CAMARA_H
