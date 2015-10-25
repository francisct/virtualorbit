#include "stdafx.h"

#include "..\glew\glew.h"		// include GL Extension Wrangler

#include "..\glfw\glfw3.h"  // include GLFW helper library

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"

#include "Controls.hpp"

#include "glm.hpp"
#include <vector>

extern GLuint view_matrix_id;
extern GLuint model_matrix_id;
extern GLuint proj_matrix_id;

extern glm::mat4 proj_matrix;
extern glm::mat4 view_matrix;

class Shape {

public: 

	GLuint vao;
	GLuint vbo;
	glm::mat4 model = glm::mat4(1.0);
	std::vector<glm::vec3> points;
	float speed = 2.0f;

	float animationSpeed = 0.5f;

	Shape::Shape(){}

	void Shape::generateMVP() {
		computeMatricesFromInputs();
		proj_matrix = getProjectionMatrix();
		view_matrix = getViewMatrix();
	}

	void Shape::passMVPtoShader() {
		generateMVP();
		glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(proj_matrix));
		glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model));
	}

	void Shape::initObj() {
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		if (points.size() > 0) {
			glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
			glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(points[0]), &points[0], GL_STATIC_DRAW);
		}
		else {
			glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
		}
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	void Shape::draw() {
		passMVPtoShader();

		glBindVertexArray(vao);
		initObj();
		glDrawArrays(GL_TRIANGLES, 0, points.size());
		glBindVertexArray(0);
	}

	void Shape::rotateLeft() {
		float liveRotation = 1.5708f / 20;
		float totalRotation = 0.0f;
		while (totalRotation < 1.5708f) {
			glm::mat4 rotate = glm::rotate(glm::mat4(1.0), liveRotation, glm::vec3(0, 1, 0));
			model = model * rotate;
			passMVPtoShader();

			totalRotation += liveRotation;
		}
	}
	void Shape::rotateRight() {
		float liveRotation = 1.5708f / 20;
		float totalRotation = 0.0f;
		while (totalRotation < 1.5708f) {
			glm::mat4 rotate = glm::rotate(glm::mat4(1.0), -liveRotation, glm::vec3(0, 1, 0));
			model = model * rotate;
			passMVPtoShader();

			totalRotation += liveRotation;
		}
	}
	void Shape::goUp() {
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0, speed, 0));
		model = model * translate;
	}
	void Shape::goDown() {
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0, -speed, 0));
		model = model * translate;
	}
	void Shape::goRight() {
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(speed, 0, 0));
		model = model * translate;
	}
	void Shape::goLeft() {
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(-speed, 0, 0));
		model = model * translate;
	}

};