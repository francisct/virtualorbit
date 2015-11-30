#include "SceneFactory.h"


SceneFactory::SceneFactory(World *world) {
	this->world = world;
}

void SceneFactory::buildAtom() {
	//nucleus:
    world->player.shape = new Sphere();
	world->player.shape->scale(glm::vec3(2,2,2));
	world->player.shape->color = glm::vec3(0.1, 0, 0);
	//platform:
	world->objects.push_back(new Cube(glm::vec3(10, 0.3, 10)));
	world->objects.back()->translate(glm::vec3(0, -10, 0));
	//atoms:
	world->objects.push_back(new Sphere());
	world->objects.back()->translate(glm::vec3(-6, -6, 0));
	world->objects.back()->color = glm::vec3(0, 0, 0.1);
	world->objects.back()->rotateAround(world->player.shape);

	world->objects.push_back(new Sphere());
	world->objects.back()->translate(glm::vec3(5, 0, 5));
	world->objects.back()->color = glm::vec3(0, 0, 0.1);
	world->objects.back()->rotateAround(world->player.shape);

	world->objects.push_back(new Sphere());
	world->objects.back()->translate(glm::vec3(1, 4, 7));
	world->objects.back()->color = glm::vec3(0, 0, 0.1);
	world->objects.back()->rotateAround(world->player.shape);

	world->objects.push_back(new Sphere());
	world->objects.back()->translate(glm::vec3(2, 2, 2));
	world->objects.back()->color = glm::vec3(0, 0, 0.1);
	world->objects.back()->rotateAround(world->player.shape);
}

void SceneFactory::buildGameLevel() {
	world->player.shape = new Sphere();
	world->player.shape->translate(glm::vec3(0, 5, 0));
	world->player.shape->rotateBy(-3.14 / 2);
	world->objects.push_back(new Cube(glm::vec3(10, 0.3, 1)));
	world->objects.push_back(new Cube(glm::vec3(3, 0.3, 1)));
	world->objects.back()->translate(glm::vec3(3, 4, 0));
}