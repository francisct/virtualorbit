

#include "Timer.h"

	Timer::Timer() {
		 deltaTime = 0;
		 lastTime = 0;
		 currentTime = 0;
		 elapsedTimeRotate90 = 0;
		 elapsedTimeRotateAround = 0;

		 mouseUnpressedTime = 0;
		 keyUnpressedTime = 0;
		lastTime = glfwGetTime();
	}


	void Timer::updateElapsedTime() {
		currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);
		elapsedTimeRotate90 += deltaTime;
		elapsedTimeRotateAround += deltaTime;
		mouseUnpressedTime += deltaTime;
		keyUnpressedTime += deltaTime;
		lastTime = currentTime;
	}
