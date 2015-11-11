
#include "Transformations.h"

void Transformations::setupRotation(float speed) {
	rotationPending = true;
	incrementalRotation = 1;
	toRotate = speed;
}

void Transformations::resetRotation() {
	rotationPending = false;
	incrementalRotation = 0.0f;
	toRotate = 0.0f;
}

void Transformations::rotateBy(float angle) {
	//based on the old rotation matrix I add append my new rotation
	rotation = glm::rotate(rotation, angle, glm::vec3(0, 1, 0));
}
//rotate objects by 90 with an animation
void Transformations::rotate90(float speed) {
	if (incrementalRotation == 0) {
		//registering rotation variables
		setupRotation(speed);
	}
	if (incrementalRotation*speed <= ROTATION_90 && incrementalRotation*speed >= -ROTATION_90) {
		if (timer.elapsedTime >= roationTimeLimit) {
			rotation = glm::rotate(rotation, speed, glm::vec3(0, 1, 0));

			incrementalRotation++;
			timer.reset();
		}
	}
	else {
		resetRotation();
	}

}

void Transformations::translate(glm::vec3 travelTo) {
	//based on the old translation matrix I add append my new translation
	translation = glm::translate(translation, travelTo);
}

glm::mat4 Transformations::swapXandY(const glm::mat4 &toSwap) {
	glm::mat4 isSwapped = glm::mat4(toSwap[0][1], toSwap[0][0], toSwap[0][2], toSwap[0][3],
		toSwap[1][1], toSwap[1][0], toSwap[1][2], toSwap[1][3],
		toSwap[2][1], toSwap[2][0], toSwap[2][2], toSwap[2][3],
		toSwap[3][1], toSwap[3][0], toSwap[3][2], toSwap[3][3]);
	return isSwapped;
}