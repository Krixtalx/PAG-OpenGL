//
// Created by Niskp on 31/10/2021.
//

#ifndef PAG_MATERIAL_H
#define PAG_MATERIAL_H

#include <GL/glew.h>
#include <glm/vec3.hpp>

namespace PAG {
	class Material {
	private:
		glm::vec3 ambiente;
		glm::vec3 difuso;
		glm::vec3 especular;
		GLuint phong;
	public:
		Material(const glm::vec3 &ambiente, const glm::vec3 &difuso, const glm::vec3 &especular, GLuint phong);

		const glm::vec3 &getAmbiente() const;

		const glm::vec3 &getDifuso() const;

		const glm::vec3 &getEspecular() const;

		GLuint getPhong() const;
	};
}


#endif //PAG_MATERIAL_H
