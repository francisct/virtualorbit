#pragma once
#include "glm.hpp"
#include "..\glew\glew.h"		// include GL Extension Wrangler
#include "..\glfw\glfw3.h"  // include GLFW helper library
#include "GL.h"
class MVP {
public:
	GLuint rDepthmatrixID;
	GLuint rMvpID;
	GLuint rViewID;
	GLuint rModelID;
	GLuint rDepthBiasID;
	GLuint rShadowMapID;

	GLuint sViewID;
	GLuint sModelID;
	GLuint sProjID;

	// Get a handle for our "LightPosition" uniform
	GLuint lightInvDirID;

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	void generateIDs(GL gl);
};
