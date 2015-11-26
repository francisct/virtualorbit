#include "Light.h"
#include "World.h"

extern World world;

Light::Light() {}

Light::Light(Shape *toCopy) :Shape(toCopy->vertices, toCopy->uvs, toCopy->normals) {
	translate(glm::vec3(0, 10, 0));
}

Light::Light(glm::vec3 ratio, Shape *toCopy) : Shape(ratio, toCopy->vertices, toCopy->uvs, toCopy->normals) {
	translate(glm::vec3(0, 10, 0));
}

void Light::turnOn() {
	color = glm::vec3(1,1,1);
}

void Light::turnOff() {
	color = glm::vec3(0, 0, 0);
}

void Light::generateIDs(GLuint shaderProgram) {
	lightPosID = glGetUniformLocation(shaderProgram, "LightPosition_worldspace");
	lightDirID = glGetUniformLocation(shaderProgram, "LightDirection_cameraspace");
	colorID = glGetUniformLocation(shaderProgram, "myColor");
}

void Light::sendToShader() {
	glUniform3f(lightPosID, pos.x, pos.y, pos.z);
	glUniform3f(lightDirID, dir.x, dir.y, dir.z);
}

void Light::drawShadow() {
	/*model = translation * rotation * scalation;
	world.shadows. sendToShaderForShadowCalculations(&model, &world.light);
	//send emtpy vertices:
		glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	vector<glm::vec3> salut;
	salut.push_back(glm::vec3(1, 1, 1));
		glBufferData(GL_ARRAY_BUFFER, salut.size() * sizeof(salut[0]), &salut[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, salut.size());*/
}

void Light::drawObject() {}