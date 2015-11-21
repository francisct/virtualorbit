#pragma once
#include "glm.hpp"
#include "..\glew\glew.h"		// include GL Extension Wrangler
#include "..\glfw\glfw3.h"  // include GLFW helper library

class Shadows {
public:
	GLuint depthMatrixID = 0;
	void generateIDs(GLuint shaderProgram);
};
