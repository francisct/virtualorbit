#pragma once

#include "Shape.h"

class Cube : public Shape {
public:
	Cube();
	Cube(glm::vec3 ratio);
};