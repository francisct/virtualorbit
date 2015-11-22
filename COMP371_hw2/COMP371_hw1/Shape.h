#pragma once

#include "..\glew\glew.h"		// include GL Extension Wrangler
#include "..\glfw\glfw3.h"  // include GLFW helper library
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


#include <vector>
#include <iostream>

#include "Timer.h"

#define PI 3.14159265359




class Shape {

	struct ToRotateAround {
		bool rotateAroundActivated = false;
		Shape *obj;
		float r = 0.0f;
		float p = 0.0f;
		float t = 0.0f;
		
		float initialT = 0.0f;
		float initialP = 0.0f;
		float toIncrementT = 0.0f;
		float toIncrementP = 0.0f;

	};

public:

	glm::vec3 pos = glm::vec3(0,0,0);
	GLuint vao;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 rotation;
	glm::mat4 translation;
	glm::mat4 scalation;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;


	float incrementalRotation = 0.0f;
	float toRotate = 0.0f;
	float roationTimeLimit = 0.01f;
	bool rotationPending = false;
	
	ToRotateAround tra = ToRotateAround();

	Shape();
	Shape(std::vector<glm::vec3> inV, std::vector<glm::vec2> inU, std::vector<glm::vec3> inN);
	Shape(glm::vec3 transform, std::vector<glm::vec3> inV, std::vector<glm::vec2> inU, std::vector<glm::vec3> inN);
	void generateMVP();
	void passMVPtoShader();
	void sendVertices();
	void sendUVs();
	void sendNormals();
	void drawObject();
	void drawShadow();
	void setupRotation(float speed);
	void resetRotation();
	void rotateBy(float angle);
	void rotateAround(Shape *shape);
	virtual void rotate90(float speed);
	virtual void translate(glm::vec3 travelTo);
	void scale(glm::vec3 multiplier);
	glm::mat4 swapXandY(const glm::mat4 &toSwap);

private:
	void computeInitialPhiAndTheta(Shape *shape);
	void setupRotateAround(Shape *shape);


};