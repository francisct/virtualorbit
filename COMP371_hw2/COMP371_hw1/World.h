#pragma once

#include <vector>
using namespace std;

#include "..\glew\glew.h"		// include GL Extension Wrangler
#include "..\glfw\glfw3.h"  // include GLFW helper library
#include "glm.hpp"

#include "Shape.h"
#include "Sphere.h"
#include "Cube.h"
#include "Player.h"
#include "Light.h"

class World {

public:

	vector<Shape*> objects;
	Player player;
	Light light;
	Shape cubeTemplate;
	Shape sphereTemplate;
	World();
	//void registerVAOS(vector<GLuint>* vaos);
	void addPlayer();
	void draw();
	void rotateWorld(float speed);
	void translate(glm::vec3 translateBy);
	void generateCubeOnClickCallback();
	void destroy();

};