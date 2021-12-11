//
// Created by Niskp on 31/10/2021.
//

#include <vector>
#include <stdexcept>
#include "Material.h"
#include "lodepng.h"

PAG::Material::Material(const glm::vec3 &ambiente, const glm::vec3 &difuso, const glm::vec3 &especular, GLuint phong)
		: ambiente(ambiente), difuso(difuso), especular(especular), phong(phong), idTextura(UINT_MAX) {}

/**
 * Constructor parametrizado de Material.
 * @param ambiente valor ambiente del material
 * @param difuso valor difuso del material
 * @param especular valor especular del material
 * @param phong exponente especular del material
 * @param path ruta en la que se encuentra la textura a cargar
 */
PAG::Material::Material(const glm::vec3 &ambiente, const glm::vec3 &difuso, const glm::vec3 &especular, GLuint phong,
                        std::string path) : ambiente(ambiente), difuso(difuso), especular(especular), phong(phong),
                                            idTextura(UINT_MAX) {
	std::vector<unsigned char> imagen; // Los píxeles de la imagen
	unsigned ancho, alto;
	unsigned error = lodepng::decode(imagen, ancho, alto, path);
	if (error) {
		std::string mensaje = path + " no se pudo cargar";
		throw std::runtime_error(mensaje);
	}
	// La textura se carga del revés, así que vamos a darle la vuelta
	unsigned char *imgPtr = &imagen[0];
	int numeroDeComponentesDeColor = 4;
	int incrementoAncho = ancho * numeroDeComponentesDeColor; // Ancho en bytes
	unsigned char *top = nullptr;
	unsigned char *bot = nullptr;
	unsigned char temp = 0;
	for (int i = 0; i < alto / 2; i++) {
		top = imgPtr + i * incrementoAncho;
		bot = imgPtr + (alto - i - 1) * incrementoAncho;
		for (int j = 0; j < incrementoAncho; j++) {
			temp = *top;
			*top = *bot;
			*bot = temp;
			++top;
			++bot;
		}
	}
	glGenTextures(1, &idTextura);
	glBindTexture(GL_TEXTURE_2D, idTextura);
	// Cómo resolver la minificación. En este caso, le decimos que utilice mipmaps, y que aplique interpolación lineal
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// Cómo resolver la magnificación. En este caso, le decimos que utilice mipmaps, y que aplique interpolación lineal
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// Cómo pasar de coordenadas de textura a coordenadas en el espacio de la textura en horizontal
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// Cómo pasar de coordenadas de textura a coordenadas en el espacio de la textura en vertical
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Finalmente, pasamos la textura a OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, imagen.data());
	glGenerateTextureMipmap(idTextura);
}

PAG::Material::~Material() {
	glDeleteTextures(1, &idTextura);
}

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

GLuint PAG::Material::getIdTextura() const {
	return idTextura;
}