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

void Light::registerAsUniform(GLuint shader_program) {
	lightPosID = glGetUniformLocation(shader_program, "LightPosition_worldspace");
	lightDirID = glGetUniformLocation(shader_program, "LightDirection_cameraspace");
}

void Light::sendToShader() {
	glUniform3f(lightPosID, pos.x, pos.y, pos.z);
	glUniform3f(lightDirID, dir.x, dir.y, dir.z);
}