#include "SceneFactory.h"


SceneFactory::SceneFactory(World *world) {
	this->world = world;
}

void SceneFactory::buildAtom() {
	world->player.shape = new Sphere();
	world->player.shape->translate(glm::vec3(0, 10, 0));
	world->player.shape->scale(glm::vec3(2,2,2));
	world->objects.push_back(new Cube(glm::vec3(10, 0.3, 10)));

	//atoms:
	world->objects.push_back(new Sphere());
	world->objects.back()->translate(glm::vec3(4,14, 0));

	world->objects.push_back(new Sphere());
	world->objects.back()->translate(glm::vec3(-5, 5, -2));

	world->objects.push_back(new Sphere());
	world->objects.back()->translate(glm::vec3(6, 8, 3));
}

void SceneFactory::buildGameLevel() {
	world->player.shape = new Sphere();
	world->player.shape->translate(glm::vec3(0, 5, 0));
	world->player.shape->rotateBy(-3.14 / 2);
	world->objects.push_back(new Cube(glm::vec3(10, 0.3, 1)));
	world->objects.push_back(new Cube(glm::vec3(3, 0.3, 1)));
	world->objects.back()->translate(glm::vec3(3, 4, 0));
}