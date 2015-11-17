
//OBJECT COMPOSITE CLASS

#include "World.h"
#include "ObjLdr.h"


World::World() {
	loadOBJ("cube.obj", templateVertices, templateUvs, templateNormals);
}

void World::registerVAOS(vector<GLuint>* vaos) {

	vaos->push_back(player.vao);
	for (int i = 0; i < objects.size(); i++) {
		vaos->push_back(objects[i].vao);
	}

	glGenVertexArrays(objects.size()+1, &vaos->at(0));
}

void World::addPlayer() {
	player = Player(0, 0, templateVertices, templateUvs, templateNormals);
}

void World::addShape(float widthRatio, float heightRatio, float depthRatio, float xTranslation, float yTranslation, float zTranslation) {

	vector<glm::vec3> vertices = templateVertices;
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].x = vertices[i].x * widthRatio + xTranslation;
		vertices[i].y = vertices[i].y * heightRatio + yTranslation;
		vertices[i].z = vertices[i].z * depthRatio + zTranslation;
	}

	objects.push_back(Shape(0, 0, vertices, templateUvs, templateNormals));
}

void World::draw() {

	for (int i = 0; i < objects.size(); i++) {
		player.draw();
		objects[i].draw();
	}
}

void World::rotateWorld(float speed) {

	for (int i = 0; i < objects.size(); i++) {
		player.rotate90(speed);
		objects[i].rotate90(speed);
	}
}

void World::translate(glm::vec3 translateBy) {

	for (int i = 0; i < objects.size(); i++) {
		player.translate(translateBy);
		objects[i].translate(translateBy);
	}
}

void World::destroy() {
	//deleting buffers
	for (int i = 0; i < objects.size(); i++) {
		glDeleteBuffers(1, &objects[i].vertexbuffer);
		glDeleteBuffers(1, &objects[i].uvbuffer);
		glDeleteBuffers(1, &objects[i].normalbuffer);
	}
}
