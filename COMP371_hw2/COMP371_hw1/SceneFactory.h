#pragma once
#include "World.h"

class SceneFactory {
public:
	World *world;

	SceneFactory(World *world);
	void buildAtom();
	void buildGameLevel();
	void objComparator();

};