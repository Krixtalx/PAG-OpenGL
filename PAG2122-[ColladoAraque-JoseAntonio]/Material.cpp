//
// Created by Niskp on 31/10/2021.
//

#include "Material.h"

PAG::Material::Material(const glm::vec3 &ambiente, const glm::vec3 &difuso, const glm::vec3 &especular, GLuint phong)
		: ambiente(ambiente), difuso(difuso), especular(especular), phong(phong) {}

const glm::vec3 &PAG::Material::getAmbiente() const {
	return ambiente;
}

const glm::vec3 &PAG::Material::getDifuso() const {
	return difuso;
}

const glm::vec3 &PAG::Material::getEspecular() const {
	return especular;
}

GLuint PAG::Material::getPhong() const {
	return phong;
}
