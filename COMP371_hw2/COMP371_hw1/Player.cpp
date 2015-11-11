
#include "Player.h"

    Player::Player():Shape() {
		flashlightPos = glm::vec3(0,2,2);
	}
	Player::Player(float xTranslation, float zRotation, std::vector<glm::vec3> inV, std::vector<glm::vec2> inU, std::vector<glm::vec3> inN):Shape(xTranslation, zRotation, inV, inU, inN){
		flashlightPos = glm::vec3(0, 2, 2);
	}
	void Player::jump() {

	}
	void Player::translate(glm::vec3 travelTo){
		Shape::translate(travelTo);
		flashlightPos += travelTo;
	}

	void Player::rotate90(float speed) {
		Shape::rotate90(speed);
		//translation = swapXandY(translation);
	}
