#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "..\glew\glew.h"		// include GL Extension Wrangler
#include "..\glfw\glfw3.h"  // include GLFW helper library
#include "Light.h"
class Shadows {
public:
	GLuint depthMatrixID = 0;
	GLuint depthShader;
	GLuint depthBiasID;
	GLuint shadowMapID;
	Shadows();
	Shadows(GLuint depthShader);
	void generateIDs(GLuint shaderID);
	glm::mat4 sendToShaderForShadowCalculations(glm::mat4 *model, Light *light);
	void sendToShaderForObjectCalculations(glm::mat4 *dephtBiasMVP);
	void activateDepthTexture(GLuint depthTexture);
};
