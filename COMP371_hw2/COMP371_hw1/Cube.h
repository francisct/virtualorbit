#pragma once

#include "Shape.h"

class Cube : public Shape {

public:

	Cube();
	Cube(float size, float width, float height, glm::vec3 position);

};