#include "Light.h"

Light::Light() {
	pos = glm::vec3(0,0,0);
	dir = glm::vec3( 0, 0, 1);
}

void Light::turnOn() {
	color = glm::vec3(1,1,1);
}

void Light::turnOff() {
	color = glm::vec3(0, 0, 0);
}

void Light::generateIDs(GLuint shaderProgram) {
	lightPosID = glGetUniformLocation(shaderProgram, "LightPosition_worldspace");
	lightDirID = glGetUniformLocation(shaderProgram, "LightDirection_cameraspace");
}

void Light::sendToShader() {
	glUniform3f(lightPosID, pos.x, pos.y, pos.z);
	glUniform3f(lightDirID, dir.x, dir.y, dir.z);
}