#pragma once

#include "Shape.h"

class Player {

public:
	Shape *shape;
	Player();
	Player(Shape *shape);
	void jump();

};