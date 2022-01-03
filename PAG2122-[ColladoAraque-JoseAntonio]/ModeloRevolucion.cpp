//
// Created by Niskp on 29/12/2021.
//

#include <stdexcept>
#include "ModeloRevolucion.h"
#include "ShaderManager.h"
#include "MaterialManager.h"


PAG::ModeloRevolucion::ModeloRevolucion(const std::string &shaderProgram, glm::vec3 pos, glm::vec3 rot, glm::vec3 sca)
		: Modelo(shaderProgram, "NULL", pos, rot, sca) {
	cargaModeloCilindro();
}


PAG::ModeloRevolucion::ModeloRevolucion(ModeloRevolucion &orig) : Modelo(orig),
                                                                  divLaterales(orig.divLaterales) {}

/**
 * Sobrecarga de la función dibujarModelo de Modelo. En esencia, hace lo mismo pero adaptando el modo de dibujado
 * al utilizado en el modelo de revolución (GL_TRIANGLE_STRIP para el lateral y GL_TRIANGLE_FAN para las tapas)
 * @param matrizMVP
 * @param matrizMV
 * @param matrizMS
 * @param tipoLuz
 */
void PAG::ModeloRevolucion::dibujarModelo(glm::mat4 matrizMVP, glm::mat4 matrizMV, glm::mat4 matrizMS,
                                          PAG::tipoLuz tipoLuz) {
	if (visible)
		try {
			matrizMVP = matrizMVP * mModelado;
			matrizMV = matrizMV * mModelado;
			matrizMS = matrizMS * mModelado;

			PAG::ShaderManager::getInstancia()->activarSP(shaderProgram);
			PAG::ShaderManager::getInstancia()->setUniform(this->shaderProgram, "matrizMVP", matrizMVP);
			PAG::ShaderManager::getInstancia()->setUniform(this->shaderProgram, "matrizMV", matrizMV);
			PAG::ShaderManager::getInstancia()->setUniform(this->shaderProgram, "matrizMS", matrizMS);
			std::vector<std::string> nombreUniforms = {"luzElegida", "colorElegido", "normalMap"};

			if (modo == PAG::wireframe) {
				std::vector<std::string> nombreSubrutinas = {"colorDefecto", "colorMaterial", "noUsarNormalMap"};
				PAG::ShaderManager::getInstancia()->activarMultiplesSubrutinas(this->shaderProgram, GL_FRAGMENT_SHADER,
				                                                               nombreUniforms, nombreSubrutinas);
			} else {
				glm::vec3 ambiente = PAG::MaterialManager::getInstancia()->getMaterial(
						this->material)->getAmbiente();
				glm::vec3 difusa = PAG::MaterialManager::getInstancia()->getMaterial(
						this->material)->getDifuso();
				glm::vec3 especular = PAG::MaterialManager::getInstancia()->getMaterial(
						this->material)->getEspecular();
				GLuint phong = PAG::MaterialManager::getInstancia()->getMaterial(
						this->material)->getPhong();
				PAG::ShaderManager::getInstancia()->setUniform(this->shaderProgram, "Ka", ambiente);
				PAG::ShaderManager::getInstancia()->setUniform(this->shaderProgram, "Kd", difusa);
				PAG::ShaderManager::getInstancia()->setUniform(this->shaderProgram, "Ks", especular);
				PAG::ShaderManager::getInstancia()->setUniform(this->shaderProgram, "phong", phong);

				std::vector<std::string> nombreSubrutinas;
				if (tipoLuz == PAG::tipoLuz::ambiente) {
					nombreSubrutinas.emplace_back("luzAmbiente");
				} else if (tipoLuz == PAG::tipoLuz::puntual) {
					nombreSubrutinas.emplace_back("luzPuntual");
				} else if (tipoLuz == PAG::tipoLuz::direccional) {
					nombreSubrutinas.emplace_back("luzDireccional");
				} else {
					nombreSubrutinas.emplace_back("luzFoco");
				}

				GLuint idTextura = MaterialManager::getInstancia()->getMaterial(material)->getIdTextura(
						PAG::texturaColor);
				GLuint idNormalMap = MaterialManager::getInstancia()->getMaterial(material)->getIdTextura(
						PAG::normalMap);
				if (usarTexturas && usarNormalMap && idTextura != UINT_MAX && idNormalMap != UINT_MAX) {
					nombreSubrutinas.emplace_back("colorTextura");
					nombreSubrutinas.emplace_back("siUsarNormalMap");
					ShaderManager::getInstancia()->setUniform(shaderProgram, "muestreador", (GLint) 0);
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, idTextura);

					ShaderManager::getInstancia()->setUniform(shaderProgram, "muestreadorNormalMap", (GLint) 1);
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, idNormalMap);
				} else if (usarTexturas && idTextura != UINT_MAX) {
					nombreSubrutinas.emplace_back("colorTextura");
					nombreSubrutinas.emplace_back("noUsarNormalMap");
					ShaderManager::getInstancia()->setUniform(shaderProgram, "muestreador", (GLint) 0);
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, idTextura);
				} else {
					nombreSubrutinas.emplace_back("colorMaterial");
					nombreSubrutinas.emplace_back("noUsarNormalMap");
				}

				PAG::ShaderManager::getInstancia()->activarMultiplesSubrutinas(this->shaderProgram, GL_FRAGMENT_SHADER,
				                                                               nombreUniforms, nombreSubrutinas);
			}

			dibujarModeloRevolucion();

		} catch (std::runtime_error &e) {
			throw e;
		}
}

/**
 * Dibuja el modelo tal y como se requiere para el calculo del mapa de sombras
 */
void PAG::ModeloRevolucion::dibujarModeloParaSombras() {
	if (visible)
		dibujarModeloRevolucion();
}

/**
 * Dibuja el modelo de revolución usando GL_TRIANGLE_STRIP para el lateral y GL_TRIANGLE_FAN para las tapas
 */
void PAG::ModeloRevolucion::dibujarModeloRevolucion() {
	glBindVertexArray(idVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO[modo]);
	glPolygonMode(GL_FRONT_AND_BACK, getGLDrawMode(modo));
	GLsizei offset = ibos[modo].size() - (2 * (divLaterales + 2) + 2);
	glDrawElements(GL_TRIANGLE_STRIP, offset, GL_UNSIGNED_INT, nullptr);
	glDrawElements(GL_TRIANGLE_FAN, divLaterales + 2, GL_UNSIGNED_INT, (GLvoid *) (offset * sizeof(GLuint)));
	offset += divLaterales + 3;
	glDrawElements(GL_TRIANGLE_FAN, divLaterales + 2, GL_UNSIGNED_INT, (GLvoid *) (offset * sizeof(GLuint)));
}

/**
 * Función auxiliar para rotar 270º los vectores
 * @param v
 */
void swapAndRotate(glm::vec3 &v) {
	v.x = v.x + v.y;
	v.y = v.x - v.y;
	v.x -= v.y;
	v.y = -v.y;
}

/**
 * Función encargada de generar todos los valores del modelo de revolución usando la generatriz y el nº de divisiones laterales
 */
void PAG::ModeloRevolucion::generarModeloRevolucion() {
	float delta = 360.0f / divLaterales;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normales;
	std::vector<glm::vec2> textura;
	std::vector<glm::vec3> tangentes;
	std::vector<glm::vec3> bitangentes;
	std::vector<glm::vec3> nG; //Normales generatriz
	std::vector<GLuint> ibo;

	float longitudTotalGeneratriz = 0;

	//Invertimos la generatriz en caso de que el orden no sea el correcto (Debe de ir de arriba a abajo)
	if (generatriz[0].y < generatriz[generatriz.size() - 1].y) {
		std::reverse(generatriz.begin(), generatriz.end());
	}

	//Calculamos las normales de la generatriz
	for (int i = 0; i < generatriz.size(); ++i) {
		if (i == 0) {
			glm::vec3 v1(0, 1, 0);
			glm::vec3 v2 = generatriz[i] - generatriz[i + 1];
			swapAndRotate(v2);
			glm::vec3 vFinal = (v1 + v2) / 2.0f;
			nG.push_back(glm::normalize(vFinal));
		} else {
			if (i == generatriz.size() - 1) {
				glm::vec3 v1 = generatriz[i - 1] - generatriz[i];
				glm::vec3 v2(0, -1, 0);
				swapAndRotate(v1);
				glm::vec3 vFinal = (v1 + v2) / 2.0f;
				nG.push_back(glm::normalize(vFinal));
			} else {
				glm::vec3 v1 = generatriz[i - 1] - generatriz[i];
				glm::vec3 v2 = generatriz[i] - generatriz[i + 1];
				swapAndRotate(v1);
				swapAndRotate(v2);
				glm::vec3 vFinal = (v1 + v2) / 2.0f;
				nG.push_back(glm::normalize(vFinal));
			}
			longitudTotalGeneratriz += glm::distance(generatriz[i], generatriz[i - 1]);
		}
	}

	//Calculamos todos los valores de cada división lateral
	float acum = 0;
	for (int i = 0; i < generatriz.size(); i++) {
		if (i > 0)
			acum += glm::distance(generatriz[i], generatriz[i - 1]);
		for (int s = 0; s <= divLaterales; ++s) {
			float angulo = glm::radians(delta * s);
			vertices.emplace_back(generatriz[i].x * cos(angulo), generatriz[i].y, -generatriz[i].x * sin(angulo));
			glm::vec3 normal(nG[i].x * cos(angulo), nG[i].y, -nG[i].x * sin(angulo));
			normales.push_back(normal);

			float u = (float) s / divLaterales;
			float v = acum / longitudTotalGeneratriz;
			textura.emplace_back(u, v);

			glm::vec3 tangente(-sin(angulo), 0, -cos(angulo));
			glm::vec3 bitangente = glm::cross(normal, tangente);

			tangentes.push_back(tangente);
			bitangentes.push_back(bitangente);
		}
	}

	//Creamos el IBO para las divisiones laterales. Esta pensado para dibujarse con GL_TRIANGLE_STRIP
	for (int s = 0; s < divLaterales; ++s) {
		for (int i = 0; i < generatriz.size(); ++i) {
			ibo.push_back(i * (divLaterales + 1) + (s + 1));
			ibo.push_back(i * (divLaterales + 1) + s);
		}
		ibo.push_back(0xFFFF);
	}

	//Añadimos los valores de los vertices centrales de la tapa superior
	vertices.emplace_back(0, generatriz[0].y, 0);
	normales.emplace_back(0, 1, 0);
	textura.emplace_back(.5, .5);
	tangentes.emplace_back(1, 0, 0);
	bitangentes.emplace_back(0, 0, 1);

	//Añadimos al final del ibo los vertices de la tapa superior. Esta pensado para dibujarse con GL_TRIANGLE_FAN
	ibo.push_back(vertices.size() - 1);
	for (int s = 0; s <= divLaterales + 1; ++s) {
		ibo.push_back(s);
	}
	//Añadimos los valores de los vertices centrales de la tapa inferior
	vertices.emplace_back(0, generatriz[generatriz.size() - 1].y, 0);
	normales.emplace_back(0, -1, 0);
	textura.emplace_back(.5, .5);
	tangentes.emplace_back(1, 0, 0);
	bitangentes.emplace_back(0, 0, 1);

	//Añadimos al final del ibo los vertices de la tapa inferior. Esta pensado para dibujarse con GL_TRIANGLE_FAN
	ibo.push_back(vertices.size() - 1);
	for (int s = 0; s <= divLaterales + 1; ++s) {
		ibo.push_back(vertices.size() - 3 - s);
	}


	nuevoVBO(PAG::posicion, vertices, GL_STATIC_DRAW);
	nuevoVBO(PAG::normal, normales, GL_STATIC_DRAW);
	nuevoVBO(PAG::textura, textura, GL_STATIC_DRAW);
	nuevoVBO(PAG::tangente, tangentes, GL_STATIC_DRAW);
	nuevoVBO(PAG::bitangente, bitangentes, GL_STATIC_DRAW);
	nuevoIBO(PAG::mallaTriangulos, ibo, GL_STATIC_DRAW);
	nuevoIBO(PAG::wireframe, ibo, GL_STATIC_DRAW);
}

/**
 * Crea un modelo de revolución básico (Cilindro)
 */
void PAG::ModeloRevolucion::cargaModeloCilindro() {
	generatriz.emplace_back(.4, 1, 0);
	generatriz.emplace_back(.4, .5, 0);
	generatriz.emplace_back(.4, 0, 0);
	divLaterales = 15;
	generarModeloRevolucion();

	mModelado = glm::translate(glm::mat4(1.0f), {1, 0, 0});
}
