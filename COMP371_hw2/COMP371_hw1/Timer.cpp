

#include "Timer.h"

	Timer::Timer() {
		deltaTime = 0;
		lastTime = glfwGetTime();
		currentTime = 0;
		elapsedTime = 0;
		mouseUnpressedTime = 0;
	}

	void Timer::reset() {
		elapsedTime = 0;
	}

	float Timer::getElapsedTime() {
		currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);
		elapsedTime += deltaTime;
		mouseUnpressedTime += deltaTime;
		lastTime = currentTime;

		return elapsedTime;
	}
