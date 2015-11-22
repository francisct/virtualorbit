#pragma once

#include "Shape.h"
#include "glm.hpp"

class Cam : public Shape {

public:
	Cam();
	float initialFoV = 45.0f;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::vec3 direction = glm::vec3(0, 0, -1);
	glm::vec3 position = glm::vec3(0, 0, 25);
	GLuint view_matrix_id = 0;
	GLuint model_matrix_id = 0;
	GLuint proj_matrix_id = 0;

	
	void generateIDs(GLuint shaderID);
	void passMVPtoShader(const glm::mat4 *model);
};