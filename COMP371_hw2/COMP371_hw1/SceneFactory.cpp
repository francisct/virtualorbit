#include "SceneFactory.h"


SceneFactory::SceneFactory(World *world) {
	this->world = world;
}

void SceneFactory::buildAtom() {
    world->player.shape = new Sphere();
	world->player.shape->scale(glm::vec3(2,2,2));
	world->objects.push_back(new Cube(glm::vec3(10, 0.3, 10)));
	world->objects.back()->translate(glm::vec3(0, -10, 0));
	//atoms:
	//world->objects.push_back(new Sphere());
	//world->objects.back()->translate(glm::vec3(0, 0, -15));
	//world->objects.back()->rotateAround(world->player.shape);

	world->objects.push_back(new Sphere());
	world->objects.back()->translate(glm::vec3(5, 0, 5));
	//world->objects.back()->rotateAround(world->player.shape);

	world->objects.push_back(new Sphere());
	world->objects.back()->translate(glm::vec3(1, 0, 7));

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

void SceneFactory::objComparator() {

	world->player.shape = new Sphere();
	world->player.shape->translate(glm::vec3(-20, 10, 0));
	world->player.shape->scale(glm::vec3(4, 4, 4));
	world->objects.push_back(new Cube(glm::vec3(5, 5, 5)));
	world->objects.back()->translate(glm::vec3(-3, 10, 0));
	//atoms:
	world->objects.push_back(new Sphere());
	world->objects.back()->translate(glm::vec3(8, 10, 0));
	world->objects.back()->scale(glm::vec3(3, 3, 3));

	world->objects.push_back(new Cube(glm::vec3(1, 1, 1)));
	world->objects.back()->translate(glm::vec3(13, 10, 0));
	world->player.shape->scale(glm::vec3(2, 2, 2));
	world->objects.push_back(new Cube(glm::vec3(30, 0.3, 30)));
}