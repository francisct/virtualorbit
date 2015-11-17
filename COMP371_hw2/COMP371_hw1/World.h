#pragma once

#include <vector>
using namespace std;

#include "..\glew\glew.h"		// include GL Extension Wrangler
#include "..\glfw\glfw3.h"  // include GLFW helper library
#include "glm.hpp"

#include "Shape.h"
#include "Player.h"

class World {

public:

	vector<Shape> objects;
	Player player;

	std::vector<glm::vec3> templateVertices;
	std::vector<glm::vec2> templateUvs;
	std::vector<glm::vec3> templateNormals;
	World();
	void registerVAOS(vector<GLuint>* vaos);
	void addPlayer();
	void addShape(float widthRatio, float heightRatio, float depthRatio, float xTranslation, float yTranslation, float zTranslation);
	void draw();
	void rotateWorld(float speed);
	void translate(glm::vec3 translateBy);
	void destroy();

};