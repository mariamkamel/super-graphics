#pragma once
#pragma once
#include "Model.h"
#include "Primitives.h"
class woodenBox : public Model
{
public:
	woodenBox() {
		primitives = {
			new Cube(ResourceManager::getTexture("box"), vec3(0.6, 1.0, 0.f), vec3(0.f, 0.f, 0.f), vec3(0.5f)),
		};
	}

	void update() {}
	~woodenBox();
};

