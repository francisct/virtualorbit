#pragma once

#include "glm.hpp"
#include "..\glew\glew.h"

#include "Shape.h"

class Light : public Shape {

public:
	
	glm::vec3 dir = glm::vec3(0, -1, 0);
	GLuint lightPosID;
	GLuint lightDirID;
	GLuint colorID;

	Light();
	Light(Shape *toCopy);
	Light(glm::vec3 ratio, Shape *toCopy);
	void turnOn();
	void turnOff();
	void Light::generateIDs(GLuint shaderProgram);
	void Light::sendToShader();
	void drawShadow();
	void drawObject();
};