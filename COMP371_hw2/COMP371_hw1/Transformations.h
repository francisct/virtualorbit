#pragma once

#include "glm.hpp"

class Transformations {

public:

	void setupRotation(float speed);
	void resetRotation();
	void rotateBy(float angle);
	virtual void rotate90(float speed);
	virtual void translate(glm::vec3 travelTo);
	glm::mat4 swapXandY(const glm::mat4 &toSwap);

};