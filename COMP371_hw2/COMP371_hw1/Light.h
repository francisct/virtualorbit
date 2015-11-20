#pragma once

#include "glm.hpp"

class Light {

public:
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec3 dir;

	Light();
	void turnOn();
	void turnOff();
};