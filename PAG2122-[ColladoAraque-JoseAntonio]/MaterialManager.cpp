//
// Created by Niskp on 31/10/2021.
//

#include <stdexcept>
#include "MaterialManager.h"

PAG::MaterialManager *PAG::MaterialManager::instancia = nullptr;

PAG::MaterialManager *PAG::MaterialManager::getInstancia() {
	if (!instancia) {
		instancia = new MaterialManager;
	}
	return instancia;
}

PAG::MaterialManager::MaterialManager() {

}

PAG::MaterialManager::~MaterialManager() {
	for (auto &material: materiales) {
		delete material.second;
	}
}

void PAG::MaterialManager::nuevoMaterial(const std::string &nombreMaterial, PAG::Material *material) {
	materiales.insert(std::make_pair(nombreMaterial, material));
}

PAG::Material *PAG::MaterialManager::getMaterial(const std::string &nombreMaterial) {
	auto mat = materiales.find(nombreMaterial);
	if (mat != materiales.end()) {
		return mat->second;
	} else {
		throw std::runtime_error(
				"[MaterialManager]: No se ha encontrado ningun material con el nombre " + nombreMaterial);
	}
}


