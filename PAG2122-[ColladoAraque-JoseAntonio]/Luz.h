//
// Created by Niskp on 14/11/2021.
//

#ifndef PAG_LUZ_H
#define PAG_LUZ_H

#include <glm/vec3.hpp>
#include <string>
#include <glm/ext/matrix_float4x4.hpp>
#include <gl/glew.h>
#include "RenderOptions.h"

namespace PAG {
	class Luz {
	private:
		glm::vec3 ia{};
		glm::vec3 id;
		glm::vec3 is;

		glm::vec3 posicion{};
		glm::vec3 direccion{};
		float gamma{};
		GLuint exponenteBordes{};
		PAG::tipoLuz tipoLuz;

	public:
		Luz(const glm::vec3 &ia);

		Luz(const glm::vec3 &id, const glm::vec3 &is, const glm::vec3 &posicionOdireccion, const bool &puntual);

		Luz(const glm::vec3 &id, const glm::vec3 &is, const glm::vec3 &posicion, const glm::vec3 &direccion,
		    float gamma, GLuint exponenteBordes);

		void aplicarLuz(const std::string &shader, const glm::mat4 &matriz) const;

		PAG::tipoLuz getTipoLuz() const;
	};
}

#endif //PAG_LUZ_H
