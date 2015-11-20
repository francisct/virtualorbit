#pragma once

#include "..\glew\glew.h"		// include GL Extension Wrangler
#include "..\glfw\glfw3.h"  // include GLFW helper library
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


#include <vector>
#include <iostream>

#include "Timer.h"

class Shape {

public:

	GLuint vao;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	glm::mat4 model;
	glm::mat4 rotation;
	glm::mat4 translation;
	glm::mat4 scalation;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	float incrementalRotation = 0.0f;
	float toRotate = 0.0f;
	float roationTimeLimit = 10.0f;
	bool rotationPending = false;
	bool translationPending = false;

	Shape();
	Shape(std::vector<glm::vec3> inV, std::vector<glm::vec2> inU, std::vector<glm::vec3> inN);
	void generateMVP();
	void passMVPtoShader();
	void initObj();
	void draw();
	void setupRotation(float speed);
	void resetRotation();
	void rotateBy(float angle);
	virtual void rotate90(float speed);
	virtual void translate(glm::vec3 travelTo);
	void scale(glm::vec3 multiplier);
	glm::mat4 swapXandY(const glm::mat4 &toSwap);

};