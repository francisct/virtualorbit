#pragma once

#include "Shape.h"

class Player : public Shape {

public:

	glm::vec3 flashlightPos;
	Player();
	Player(float xTranslation, float zRotation, std::vector<glm::vec3> inV, std::vector<glm::vec2> inU, std::vector<glm::vec3> inN);
	void jump();
	void translate(glm::vec3 travelTo);
	void rotate90(float speed);

};