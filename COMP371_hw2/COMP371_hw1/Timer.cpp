

#include "Timer.h"


	float deltaTime = 0;
	float lastTime = 0;
	float currentTime = 0;
	float elapsedTime = 0;

	Timer::Timer() {
		deltaTime = 0;
		lastTime = 0;
		currentTime = 0;
		elapsedTime = 0;
	}

	void Timer::reset() {
		elapsedTime = 0;
	}

	float Timer::getElapsedTime() {
		if (lastTime == 0) {
			lastTime = glfwGetTime();
		}
		currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);
		elapsedTime += deltaTime;
		return elapsedTime;
	}

	void Timer::updateLastTime() {
		currentTime = lastTime;
	}
