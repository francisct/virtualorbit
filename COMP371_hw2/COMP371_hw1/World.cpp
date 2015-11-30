
//OBJECT COMPOSITE CLASS

#include "World.h"
#include "ObjLdr.h"
#include "TextureLdr.h"
#include "GLOBALS.h"
#include <time.h>

extern double mouseXpos, mouseYpos;
extern Timer timer;
extern GLuint currentShader, realisticLightShader, simpleLightShader;

World::World() {}
World::World(GLuint shaderID, GLuint depthShader) {
	cubeTemplate = loadOBJ("cube.obj");
	sphereTemplate = loadOBJ("sphere.obj");

	light = Light(&cubeTemplate);
	shadows = Shadows(depthShader);
	updateShader(shaderID);

}

void World::updateShader(GLuint shaderID) {
	light.generateIDs(shaderID);
	cam.generateIDs(shaderID);
	shadows.generateIDs(shaderID);
}

void World::drawObjects(GLuint depthTexture) {
	light.sendToShader();
	shadows.activateDepthTexture(depthTexture);
	light.drawObject();
	player.shape->drawObject();
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->drawObject();
	}
	if (timer.elapsedTimeRotateAround >= ROTATE_AROUND_TIME) {
		timer.elapsedTimeRotateAround = 0;
	}

	if (timer.elapsedTimeRotate90 >= ROTATION_90_TIME) {
		timer.elapsedTimeRotate90 = 0;
	}
}
void World::drawShadows() {
	light.drawShadow();
	player.shape->drawShadow();
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->drawShadow();
	}

}

void World::rotateWorld(float speed) {

	player.shape->rotate90(speed);
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->rotate90(speed);
	}
}

void World::translate(glm::vec3 translateBy) {

	player.shape->translate(translateBy);
	for (int i = 0; i < objects.size(); i++) {
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

void World::generateShapeOnClickCallback(Shape *shape) {
	//if this is a new click and not that the button is still pressed create new shape
	if (timer.mouseUnpressedTime > 0.1) {
		objects.push_back(shape);
		objects.back()->scale(glm::vec3(0.1, 0.1, 0.1));
		objects.back()->translate(glm::vec3(light.pos.x, light.pos.y, light.pos.z - 2));
		objects.back()->rotateAround(player.shape);
		//add a random color:
		srand(time(NULL));
		glm::vec3 col;
		
		col.x = (float)(rand() % 10) / 10;
		col.y = (float)(rand() % 10) / 10;
		col.z = (float)(rand() % 10) / 10;
		objects.back()->color = col;
	}
	//get latest shape and scale it. Keeping the mouse press will continue to scale the same cube
	shape = this->objects.back();
	shape->scale(glm::vec3(1.05, 1.05, 1.05));
	std::cout << "salut";

	//reset time that mouse is unpressed
	timer.mouseUnpressedTime = 0.0;


}
