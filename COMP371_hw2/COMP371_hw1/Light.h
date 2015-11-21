#pragma once

#include "glm.hpp"
#include "..\glew\glew.h"
class Light {

public:
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec3 dir;
	GLuint lightPosID;
	GLuint lightDirID;

	Light();
	void turnOn();
	void turnOff();
	void Light::generateIDs(GLuint shaderProgram);
	void Light::sendToShader();
};