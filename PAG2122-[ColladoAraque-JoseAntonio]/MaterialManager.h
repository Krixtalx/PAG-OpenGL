//
// Created by Niskp on 31/10/2021.
//

#ifndef PAG_MATERIALMANAGER_H
#define PAG_MATERIALMANAGER_H

#include <string>
#include <map>
#include "Material.h"

namespace PAG {
	class MaterialManager {
	private:
		static MaterialManager *instancia;
		std::map<std::string, Material *> materiales;

		MaterialManager() = default;

	public:
		static MaterialManager *getInstancia();

		MaterialManager(const MaterialManager &orig) = delete;

		~MaterialManager();

		void nuevoMaterial(const std::string &nombreMaterial, Material *material);

		Material *getMaterial(const std::string &nombreMaterial);
	};
}


#endif //PAG_MATERIALMANAGER_H
