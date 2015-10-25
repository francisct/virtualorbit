#ifndef SHAPE_H
#define SHAPE_H
#include "..\glew\glew.h"		// include GL Extension Wrangler

#include "..\glfw\glfw3.h"  // include GLFW helper library

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"

#include "Controls.hpp"

#include "glm.hpp"
using namespace glm;
#include <vector>
using namespace std;

extern GLuint view_matrix_id;
extern GLuint model_matrix;
extern GLuint proj_matrix_id;

extern glm::mat4 proj_matrix;
extern glm::mat4 view_matrix;

class Shape {

public:

	GLuint vao;
	GLuint vbo;
	glm::mat4 model = glm::mat4(1.0);
	vector<vec3> points;

	Shape::Shape() {}

	void Shape::generateMVP() {
	}

	void Shape::passMVPtoShader() {
	}

	GLuint Shape::initObj() {
	}

	void Shape::draw() {
	}

};
#endif