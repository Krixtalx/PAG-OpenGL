//
// Created by Niskp on 08/10/2021.
//

#ifndef PAG_RENDEROPTIONS_H
#define PAG_RENDEROPTIONS_H

namespace PAG {
	enum modoDibujado {
		nubePuntos,
		wireframe,
		mallaTriangulos
	};

	static unsigned numModosDibujo() {
		return modoDibujado::mallaTriangulos + 1;
	}

	enum paramShader {
		posicion,
		normal,
		tangente,
		bitangente,
		textura,
		mapaNormal
	};

	static unsigned numParamShader() {
		return mapaNormal + 1;
	};

	enum tipoTextura {
		texturaColor,
		normalMap
	};

	static unsigned numTiposTextura() {
		return normalMap + 1;
	}

	enum class tipoLuz {
		ambiente,
		puntual,
		direccional,
		foco
	};

	static unsigned anchoVentanaPorDefecto = 1024;
	static unsigned altoVentanaPorDefecto = 576;

	static unsigned anchoMS = 1024;
	static unsigned altoMS = 1024;

};

#endif //PAG_RENDEROPTIONS_H
