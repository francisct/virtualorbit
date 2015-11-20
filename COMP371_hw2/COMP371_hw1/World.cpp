
//OBJECT COMPOSITE CLASS

#include "World.h"
#include "ObjLdr.h"

extern double mouseXpos, mouseYpos;
extern Timer timer;

World::World() {
	cubeTemplate = loadOBJ("cube.obj");
	sphereTemplate = loadOBJ("sphere.obj");
}
/*
void World::registerVAOS(vector<GLuint>* vaos) {

	vaos->push_back(player.vao);
	for (int i = 0; i < objects.size(); i++) {
		vaos->push_back(objects[i].vao);
	}

	glGenVertexArrays(objects.size()+1, &vaos->at(0));
}
*/
void World::addPlayer() {
	player = Player(new Sphere(glm::vec3(0,0,0), glm::vec3(0,0,0));
}


void World::draw() {

	for (int i = 0; i < objects.size(); i++) {
		player.shape->draw();
		objects[i]->draw();
	}
}

void World::rotateWorld(float speed) {

	for (int i = 0; i < objects.size(); i++) {
		player.shape->rotate90(speed);
		objects[i]->rotate90(speed);
	}
}

void World::translate(glm::vec3 translateBy) {

	for (int i = 0; i < objects.size(); i++) {
		player.shape->translate(translateBy);
		objects[i]->translate(translateBy);
	}
}

void World::destroy() {
	//deleting buffers
	for (int i = 0; i < objects.size(); i++) {
		glDeleteBuffers(1, &objects[i]->vertexbuffer);
		glDeleteBuffers(1, &objects[i]->uvbuffer);
		glDeleteBuffers(1, &objects[i]->normalbuffer);
	}
}

void World::generateCubeOnClickCallback() {
	//if this is a new click and not that the button is still pressed 
	if (timer.mouseUnpressedTime > 0.5) {
		this->addShape(0.1, 0.1, 0.1, glm::vec3(light.pos.x/2, light.pos.y/2, light.pos.z-2));	
	}
	//get latest shape and scale it. Keeping the mouse press will continue to scale the same cube
	Shape *shape = &this->objects.back();
	shape->scale(glm::vec3(1.05,1.05,1.05));
	std::cout << "salut";

	//reset time that mouse is unpressed
	timer.mouseUnpressedTime = 0.0;
	
	
}
