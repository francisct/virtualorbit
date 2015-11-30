#pragma once

#include "..\glew\glew.h"		// include GL Extension Wrangler
#include "..\glfw\glfw3.h"  // include GLFW helper library

class Timer {

public:

	float deltaTime = 0;
	float lastTime = 0;
	float currentTime = 0;
	float elapsedTimeRotate90 = 0;
	float elapsedTimeRotateAround = 0;

	float mouseUnpressedTime = 0;
	float keyUnpressedTime = 0;

	Timer();
	void updateElapsedTime();
};