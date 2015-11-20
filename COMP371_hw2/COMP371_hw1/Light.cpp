#include "Light.h"

Light::Light() {
	pos = glm::vec3(0,0,2);
	dir = glm::vec3(0, -1, 0);
}

void Light::turnOn() {
	color = glm::vec3(1,1,1);
}

void Light::turnOff() {
	color = glm::vec3(0, 0, 0);
}