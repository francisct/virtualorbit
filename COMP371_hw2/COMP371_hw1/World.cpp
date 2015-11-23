
//OBJECT COMPOSITE CLASS

#include "World.h"
#include "ObjLdr.h"
#include "TextureLdr.h"

extern double mouseXpos, mouseYpos;
extern Timer timer;
extern GLuint currentShader, realisticLightShader, simpleLightShader;

World::World() {}
World::World(GLuint shaderID, GLuint depthShader) {
	cubeTemplate = loadOBJ("cube.obj");
	sphereTemplate = loadOBJ("sphere.obj");

	shadows = Shadows(depthShader);
	updateShader(shaderID);

}

void World::updateShader(GLuint shaderID) {
	light.generateIDs(shaderID);
	cam.generateIDs(shaderID);
	shadows.generateIDs(shaderID);
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

void World::draw() {
	GLuint depthTexture = 0;
	GLuint *FramebufferName = new GLuint();

	if (currentShader == realisticLightShader) {
		depthTexture = prepareDepthTexture(FramebufferName);
		glBindFramebuffer(GL_FRAMEBUFFER, *FramebufferName);
		glViewport(0, 0, 1024, 1024);



		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glUseProgram(shadows.depthShader);
		player.shape->drawShadow();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(currentShader);
	light.sendToShader();
	shadows.activateDepthTexture(depthTexture);
	player.shape->drawObject();

	
	for (int i = 0; i < objects.size(); i++) {

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shadows.depthShader);
		objects[i]->drawShadow();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(currentShader);
		light.sendToShader();
		shadows.activateDepthTexture(depthTexture);
		objects[i]->drawObject();
	}
}

void World::drawObjects(GLuint depthTexture) {
	light.sendToShader();
	shadows.activateDepthTexture(depthTexture);
	player.shape->drawObject();
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->drawObject();
	}
}
void World::drawShadows() {

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
	}
	//get latest shape and scale it. Keeping the mouse press will continue to scale the same cube
	shape = this->objects.back();
	shape->scale(glm::vec3(1.05, 1.05, 1.05));
	std::cout << "salut";

	//reset time that mouse is unpressed
	timer.mouseUnpressedTime = 0.0;


}
