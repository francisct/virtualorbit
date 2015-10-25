#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"
using namespace glm;


#include <vector>
#include <string>
using namespace std;

class Car {
public:
	vector<glm::vec3> points;

	Car::Car();
	void Car::start();
	void Car::driveTo(glm::vec3 nextPos);
};