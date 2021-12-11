//
// Created by Niskp on 08/10/2021.
//

#include "Modelo.h"
#include "ShaderManager.h"
#include "MaterialManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <utility>
#include <stdexcept>
#include <climits>
#include <glm/gtx/transform.hpp>

/**
 * Constructor parametrizado
 * @param shaderProgram que se usará para renderizar el modelo
 * @param path ruta de la que se cargará el modelo
 */
PAG::Modelo::Modelo(std::string shaderProgram, const std::string &path, glm::vec3 pos, glm::vec3 rot) :
		shaderProgram(std::move(shaderProgram)) {

	mModelado = glm::rotate(glm::translate(pos), glm::radians(rot.x), {1, 0, 0});
	mModelado = glm::rotate(mModelado, glm::radians(rot.y), {0, 1, 0});
	mModelado = glm::rotate(mModelado, glm::radians(rot.z), {0, 0, 1});

	//Creamos nuestro VAO
	glGenVertexArrays(1, &idVAO);
	glBindVertexArray(idVAO);

	//Ponemos tanto espacios en el vector de VBO como parametros tengamos para el shader.
	idVBO.resize(PAG::numParamShader());
	vbos.resize(PAG::numParamShader());
	for (unsigned int &i: idVBO) {
		i = UINT_MAX;
	}
	//Ponemos tanto espacios en el vector de IBO como modos de dibujado tengamos.
	idIBO.resize(PAG::numModosDibujo());
	ibos.resize(PAG::numModosDibujo());
	for (unsigned int &i: idIBO) {
		i = UINT_MAX;
	}

	if (path != "NULL")
		cargaModelo(path);
}

/**
 * Constructor copia. Copia el numVertices y el shaderProgram y realiza una nueva instanciacion de los vbos e ibos
 * @param orig
 */
PAG::Modelo::Modelo(PAG::Modelo &orig) : shaderProgram(orig.shaderProgram),
                                         vbos(orig.vbos), ibos(orig.ibos), material(orig.material),
                                         mModelado(orig.mModelado) {
	//Creamos nuestro VAO
	glGenVertexArrays(1, &idVAO);
	glBindVertexArray(idVAO);

	//Ponemos tanto espacios en el vector de VBO como parametros tengamos para el shader.
	idVBO.resize(PAG::numParamShader());
	//Ponemos tanto espacios en el vector de IBO como modos de dibujado tengamos.
	idIBO.resize(PAG::numModosDibujo());

	for (int i = 0; i < vbos.size(); ++i) {
		nuevoVBO(static_cast<paramShader>(i), vbos[i], GL_STATIC_DRAW);
	}
	for (int i = 0; i < ibos.size(); ++i) {
		nuevoIBO(static_cast<modoDibujado>(i), ibos[i], GL_STATIC_DRAW);
	}
}

/**
 * Destructor. Libera todos los recursos reservados a OpenGL.
 */
PAG::Modelo::~Modelo() {
	for (unsigned int &vbo: idVBO) {
		if (vbo != UINT_MAX)
			glDeleteBuffers(1, &vbo);
	}
	for (unsigned int &ibo: idIBO) {
		if (ibo != UINT_MAX)
			glDeleteBuffers(1, &ibo);
	}
	glDeleteVertexArrays(1, &idVAO);
}

/**
 * Instancia un VBO en el contexto OpenGL y lo guarda en vbos
 * @param tipoDato parametro del shader que representa el vbo
 * @param datos a instanciar
 * @param freqAct GLenum que indica con que frecuencia se van a modificar los vertices. GL_STATIC_DRAW siempre por ahora
 */
void PAG::Modelo::nuevoVBO(PAG::paramShader tipoDato, const std::vector<glm::vec3> &datos, GLenum freqAct) {
	//Si hay un buffer de este tipo instanciado, lo eliminamos
	if (idVBO[tipoDato] != UINT_MAX) {
		glDeleteBuffers(1, &idVBO[tipoDato]);
	}
	vbos[tipoDato] = datos;
	glBindVertexArray(idVAO);
	glGenBuffers(1, &idVBO[tipoDato]);
	glBindBuffer(GL_ARRAY_BUFFER, idVBO[tipoDato]);
	glBufferData(GL_ARRAY_BUFFER, datos.size() * sizeof(glm::vec3), datos.data(), freqAct);
	glVertexAttribPointer(tipoDato, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
	                      nullptr);
	glEnableVertexAttribArray(tipoDato);
}

/**
 * Instancia un VBO en el contexto OpenGL y lo guarda en textura
 * @param tipoDato parametro del shader que representa el vbo
 * @param datos a instanciar
 * @param freqAct GLenum que indica con que frecuencia se van a modificar los vertices. GL_STATIC_DRAW siempre por ahora
 */
void PAG::Modelo::nuevoVBO(PAG::paramShader tipoDato, const std::vector<glm::vec2> &datos, GLenum freqAct) {
	//Si hay un buffer de este tipo instanciado, lo eliminamos
	if (idVBO[tipoDato] != UINT_MAX) {
		glDeleteBuffers(1, &idVBO[tipoDato]);
	}
	textura = datos;
	glBindVertexArray(idVAO);
	glGenBuffers(1, &idVBO[tipoDato]);
	glBindBuffer(GL_ARRAY_BUFFER, idVBO[tipoDato]);
	glBufferData(GL_ARRAY_BUFFER, datos.size() * sizeof(glm::vec2), datos.data(), freqAct);
	glVertexAttribPointer(tipoDato, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2),
	                      nullptr);
	glEnableVertexAttribArray(tipoDato);
}

/**
 * Instancia un IBO en el contexto OpenGL y lo guarda en ibos
 * @param modo modo de dibujado que representa el ibo
 * @param datos a instanciar
 * @param freqAct GLenum que indica con que frecuencia se van a modificar los vertices. GL_STATIC_DRAW siempre por ahora
 */
void PAG::Modelo::nuevoIBO(PAG::modoDibujado modo, const std::vector<GLuint> &datos, GLenum freqAct) {
	//Si hay un buffer de este tipo instanciado, lo eliminamos
	if (idIBO[modo] != UINT_MAX) {
		glDeleteBuffers(1, &idIBO[modo]);
	}
	ibos[modo] = datos;
	glBindVertexArray(idVAO);
	glGenBuffers(1, &idIBO[modo]);
	glBindBuffer(GL_ARRAY_BUFFER, idIBO[modo]);
	glBufferData(GL_ARRAY_BUFFER, datos.size() * sizeof(GLuint), datos.data(), freqAct);
}

/**
 * Función a la que se llama cuando se debe de dibujar el modelo
 * @param tipoLuz Tipo de luz que se esta renderizando actualmente. Es necesario para la activación de las subrutinas del shader
 */
void PAG::Modelo::dibujarModelo(glm::mat4 matrizMVP, glm::mat4 matrizMV, PAG::tipoLuz tipoLuz) {
	if (visible)
		try {
			matrizMVP = matrizMVP * mModelado;
			matrizMV = matrizMV * mModelado;
			PAG::ShaderManager::getInstancia()->activarSP(shaderProgram);
			PAG::ShaderManager::getInstancia()->setUniform(this->shaderProgram, "matrizMVP", matrizMVP);
			PAG::ShaderManager::getInstancia()->setUniform(this->shaderProgram, "matrizMV", matrizMV);
			std::vector<std::string> nombreUniforms = {"luzElegida", "colorElegido"};
			if (modo == PAG::wireframe) {
				std::vector<std::string> nombreSubrutinas = {"colorDefecto", "colorMaterial"};
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
				if (usarTexturas &&
				    MaterialManager::getInstancia()->getMaterial(material)->getIdTextura() != UINT_MAX) {
					nombreSubrutinas.emplace_back("colorTextura");
					ShaderManager::getInstancia()->setUniform(shaderProgram, "muestreador", (GLint) 0);
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D,
					              MaterialManager::getInstancia()->getMaterial(material)->getIdTextura());
				} else
					nombreSubrutinas.emplace_back("colorMaterial");

				PAG::ShaderManager::getInstancia()->activarMultiplesSubrutinas(this->shaderProgram, GL_FRAGMENT_SHADER,
				                                                               nombreUniforms, nombreSubrutinas);
			}

			glBindVertexArray(idVAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO[modo]);
			glPolygonMode(GL_FRONT_AND_BACK, getGLDrawMode(modo));
			glDrawElements(GL_TRIANGLES, ibos[modo].size(), GL_UNSIGNED_INT, nullptr);

		} catch (std::runtime_error &e) {
			throw e;
		}
}

/**
 * Crea el modelo de un triangulo
 */
void PAG::Modelo::cargaModeloTriangulo() {
	std::vector<glm::vec3> vertices = {{-.5, -.5, 0},
	                                   {.5,  -.5, 0},
	                                   {.0,  .5,  0}};
	std::vector<glm::vec3> localColores = {{1, 0, 0},
	                                       {0, 1, 0},
	                                       {0, 0, 1}};
	std::vector<GLuint> indices = {0, 1, 2};


	this->nuevoVBO(PAG::posicion, vertices, GL_STATIC_DRAW);
	this->nuevoVBO(PAG::normal, localColores, GL_STATIC_DRAW);
	this->nuevoIBO(PAG::mallaTriangulos, indices, GL_STATIC_DRAW);
	this->nuevoIBO(PAG::wireframe, indices, GL_STATIC_DRAW);
	this->setMaterial("DefaultMat");
}

/**
 * Crea el modelo de un tetraedro
 */
void PAG::Modelo::cargaModeloTetraedro() {
	std::vector<glm::vec3> vertices = {{0, 1, 0},
	                                   {0, 1, 0},
	                                   {0, 1, 0},
	                                   {0, 0, 1},
	                                   {0, 0, 1},
	                                   {0, 0, 1},
	                                   {1, 0, 0},
	                                   {1, 0, 0},
	                                   {1, 0, 0},
	                                   {0, 0, 0},
	                                   {0, 0, 0},
	                                   {0, 0, 0}};

	std::vector<glm::vec3> normales = {{-1,     0,      0}, // 0, 1, 0
	                                   {0,      0,      -1},
	                                   {0.5777, 0.5777, 0.5777},
	                                   {-1,     0,      0}, // 0, 0, 1
	                                   {0,      -1,     0},
	                                   {0.5777, 0.5777, 0.5777},
	                                   {0,      0,      -1}, // 1, 0, 0
	                                   {0,      -1,     0},
	                                   {0.5777, 0.5777, 0.5777},
	                                   {-1,     0,      0}, // 0, 0, 0
	                                   {0,      -1,     0},
	                                   {0,      0,      -1}};

	std::vector<GLuint> indices = {0, 3, 9,
	                               1, 11, 6,
	                               4, 7, 10,
	                               2, 8, 5};
	this->nuevoVBO(PAG::posicion, vertices, GL_STATIC_DRAW);
	this->nuevoVBO(PAG::normal, normales, GL_STATIC_DRAW);
	this->nuevoIBO(PAG::mallaTriangulos, indices, GL_STATIC_DRAW);
	this->nuevoIBO(PAG::wireframe, indices, GL_STATIC_DRAW);
	this->setMaterial("DefaultMat");
}


/**
 * Traduce de modoDibujado a los modos de dibujado de OpenGL
 * @param modo de modoDibujado
 * @return GLenum que indica como debe de dibujarse
 */
GLenum PAG::Modelo::getGLDrawMode(PAG::modoDibujado modo) {
	switch (modo) {
		case PAG::nubePuntos:
			return GL_POINT;
			break;
		case PAG::wireframe:
			return GL_LINE;
			break;
		default:
			return GL_FILL;
			break;
	}
}

void PAG::Modelo::setMaterial(const std::string &material) {
	Modelo::material = material;
}

const std::string &PAG::Modelo::getShaderProgram() const {
	return shaderProgram;
}

void PAG::Modelo::cargaModelo(const std::string &path) {
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate |
	                                             aiProcess_GenSmoothNormals);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		throw std::runtime_error("[Modelo::cargaModelo]: Error en la carga del modelo con Assimp");
	}

	procesarNodo(scene->mRootNode, scene);
}

void PAG::Modelo::procesarNodo(aiNode *node, const aiScene *scene) {
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		procesarMalla(mesh, scene);
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		procesarNodo(node->mChildren[i], scene);
	}
}

void PAG::Modelo::procesarMalla(aiMesh *mesh, const aiScene *scene) {
	glm::vec3 vec;
	glm::vec2 vecTex;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		vec.x = mesh->mVertices[i].x;
		vec.y = mesh->mVertices[i].y;
		vec.z = mesh->mVertices[i].z;
		vbos[PAG::posicion].push_back(vec);

		vec.x = mesh->mNormals[i].x;
		vec.y = mesh->mNormals[i].y;
		vec.z = mesh->mNormals[i].z;
		vbos[PAG::normal].push_back(vec);

		if (mesh->mTextureCoords[0]) {
			vecTex.x = mesh->mTextureCoords[0][i].x;
			vecTex.y = mesh->mTextureCoords[0][i].y;
		} else {
			vecTex = {0, 0};
		}
		textura.push_back(vecTex);
	}
	this->nuevoVBO(PAG::posicion, vbos[PAG::posicion], GL_STATIC_DRAW);
	this->nuevoVBO(PAG::normal, vbos[PAG::normal], GL_STATIC_DRAW);
	this->nuevoVBO(PAG::textura, textura, GL_STATIC_DRAW);

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			ibos[PAG::mallaTriangulos].push_back(face.mIndices[j]);
	}

	this->nuevoIBO(PAG::mallaTriangulos, ibos[mallaTriangulos], GL_STATIC_DRAW);
	this->nuevoIBO(PAG::wireframe, ibos[mallaTriangulos], GL_STATIC_DRAW);
}

void PAG::Modelo::cambiarUsoTextura() {
	usarTexturas = !usarTexturas;
}

void PAG::Modelo::cambiarModoDibujado() {
	if (modo == PAG::mallaTriangulos)
		modo = PAG::wireframe;
	else
		modo = PAG::mallaTriangulos;
}

PAG::modoDibujado PAG::Modelo::getModo() const {
	return modo;
}

void PAG::Modelo::cambiarVisibilidad() {
	visible = !visible;
}

