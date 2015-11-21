#include "Shape.h"

#include "Controls.h"
#include "ObjLdr.h"
#include "GLOBALS.h"
#include "World.h"

extern Timer timer;
extern World world;

Shape::Shape() {}
Shape::Shape(glm::vec3 ratio, std::vector<glm::vec3> inV, std::vector<glm::vec2> inU, std::vector<glm::vec3> inN) {
	model = glm::mat4(1.0);
	vertices = inV;

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].x = vertices[i].x * ratio.x;
		vertices[i].y = vertices[i].y * ratio.y;
		vertices[i].z = vertices[i].z * ratio.z;
	}

	uvs = inU;
	normals = inN;
}

Shape::Shape(std::vector<glm::vec3> inV, std::vector<glm::vec2> inU, std::vector<glm::vec3> inN) {
	model = glm::mat4(1.0);
	vertices = inV;
	uvs = inU;
	normals = inN;
}

void Shape::generateMVP() {
	computeMatricesFromInputs();
	model = translation * rotation * scalation;
	//model = scalation * rotation * translation;
}

void Shape::passMVPtoShader() {
	generateMVP();
	//registering my matrices to be used in the shaders
	world.cam.passMVPtoShader(&model);
}

void Shape::initObj() {


	//setup vbo for vertices
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	if (vertices.size() > 0) {
		//this is to reset the buffer in case there are any changes
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
	}
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);



	//setup vbo for uvs
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	if (uvs.size() > 0) {
		//this is to reset the buffer in case there are any changes
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(uvs[0]), &uvs[0], GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
	}
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);



	//setup vbo for normals
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	if (normals.size() > 0) {
		//this is to reset the buffer in case there are any changes
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
	}
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void Shape::draw() {
	if (rotationPending) {
		rotate90(toRotate);
	}
	passMVPtoShader();

	//glBindVertexArray(vao);
	initObj();
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	//glBindVertexArray(0);
}

void Shape::setupRotation(float speed) {
	rotationPending = true;
	incrementalRotation = 1;
	toRotate = speed;
	timer.reset();
}

void Shape::resetRotation() {
	rotationPending = false;
	incrementalRotation = 0.0f;
	toRotate = 0.0f;
}

void Shape::rotateBy(float angle) {
	//based on the old rotation matrix I add append my new rotation
	rotation = glm::rotate(rotation, angle, glm::vec3(0, 1, 0));
}
//rotate objects by 90 with an animation
void Shape::rotate90(float speed) {
	if (incrementalRotation == 0) {
		//registering rotation variables
		setupRotation(speed);
	}
	if (incrementalRotation*speed <= ROTATION_90 && incrementalRotation*speed >= -ROTATION_90) {
		if (timer.elapsedTime >= roationTimeLimit) {
			rotation = glm::rotate(rotation, speed, glm::vec3(0, 1, 0));

			incrementalRotation++;
			timer.reset();
		}
	}
	else {
		resetRotation();
	}

}

void Shape::translate(glm::vec3 travelTo) {
	//based on the old translation matrix I add append my new translation
	translation = glm::translate(translation, travelTo);
}

void Shape::scale(glm::vec3 multiplier) {
	scalation = glm::scale(scalation, multiplier);
}

glm::mat4 Shape::swapXandY(const glm::mat4 &toSwap) {
	glm::mat4 isSwapped = glm::mat4(toSwap[0][0], toSwap[0][0], toSwap[0][2], toSwap[0][3],
		toSwap[0][0], toSwap[1][0], toSwap[1][2], toSwap[1][3],
		toSwap[2][0], toSwap[2][0], toSwap[2][2], toSwap[2][3],
		toSwap[3][0], toSwap[3][0], toSwap[3][2], toSwap[3][3]);
	return isSwapped;
}