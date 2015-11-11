#pragma once

#include "..\glew\glew.h"		// include GL Extension Wrangler
#include "..\glfw\glfw3.h"  // include GLFW helper library

class Timer {

public:

	float deltaTime;
	float lastTime;
	float currentTime;
	float elapsedTime;

	Timer();
	void reset();
	float getElapsedTime();
	void updateLastTime();
};