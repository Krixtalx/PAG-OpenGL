//
// Created by Niskp on 29/12/2021.
//

#ifndef PAG_MODELOREVOLUCION_H
#define PAG_MODELOREVOLUCION_H

#include "Modelo.h"

namespace PAG {
	class ModeloRevolucion : public Modelo {
	private:
		std::vector<glm::vec3> generatriz;
		unsigned divLaterales = UINT_MAX;

		void generarModeloRevolucion();

		void dibujarModeloRevolucion();

		void cargaModeloCilindro();

	public:
		ModeloRevolucion(const std::string &shaderProgram, glm::vec3 pos = {0, 0, 0},
		                 glm::vec3 rot = {0, 0, 0}, glm::vec3 sca = {1, 1, 1});

		ModeloRevolucion(ModeloRevolucion &orig);

		void dibujarModelo(glm::mat4 matrizMVP, glm::mat4 matrizMV, glm::mat4 matrizMS, PAG::tipoLuz tipoLuz) override;

		void dibujarModeloParaSombras() override;
	};
}


#endif //PAG_MODELOREVOLUCION_H
