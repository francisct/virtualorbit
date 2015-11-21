#pragma once
#include "..\glew\glew.h"		// include GL Extension Wrangler
#include "..\glfw\glfw3.h"  // include GLFW helper library
#include "ShaderLdr.h"

class GL {
public:
	GLuint simpleLightShaders;
	GLuint depthShaders;
	GLuint realisticLightShaders;

	void importShaders();
	void prepareGL();
};
