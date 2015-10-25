
#include "Shape.cpp"

class Cube : public Shape {

public:

	Cube::Cube(){}

	Cube::Cube(float size) {
		points.push_back(glm::vec3(-1.0f, -1.0f, -1.0f)*size);
		points.push_back(glm::vec3(-1.0f, -1.0f, 1.0f)*size);
		points.push_back(glm::vec3(-1.0f, 1.0f, 1.0f)*size);
		points.push_back(glm::vec3(1.0f, 1.0f, -1.0f)*size);
		points.push_back(glm::vec3(-1.0f, -1.0f, -1.0f)*size);
		points.push_back(glm::vec3(-1.0f, 1.0f, -1.0f)*size);
		points.push_back(glm::vec3(1.0f, -1.0f, 1.0f)*size);
		points.push_back(glm::vec3(-1.0f, -1.0f, -1.0f)*size);
		points.push_back(glm::vec3(1.0f, -1.0f, -1.0f)*size);
		points.push_back(glm::vec3(1.0f, 1.0f, -1.0f)*size);
		points.push_back(glm::vec3(1.0f, -1.0f, -1.0f)*size);
		points.push_back(glm::vec3(-1.0f, -1.0f, -1.0f)*size);
		points.push_back(glm::vec3(-1.0f, -1.0f, -1.0f)*size);
		points.push_back(glm::vec3(-1.0f, -1.0f, -1.0f)*size);
		points.push_back(glm::vec3(-1.0f, 1.0f, 1.0f)*size);
		points.push_back(glm::vec3(-1.0f, 1.0f, -1.0f)*size);
		points.push_back(glm::vec3(1.0f, -1.0f, 1.0f)*size);
		points.push_back(glm::vec3(-1.0f, -1.0f, 1.0f)*size);
		points.push_back(glm::vec3(-1.0f, -1.0f, -1.0f)*size);
		points.push_back(glm::vec3(-1.0f, 1.0f, 1.0f)*size);
		points.push_back(glm::vec3(-1.0f, -1.0f, 1.0f)*size);
		points.push_back(glm::vec3(1.0f, -1.0f, 1.0f)*size);
		points.push_back(glm::vec3(1.0f, 1.0f, 1.0f)*size);
		points.push_back(glm::vec3(1.0f, -1.0f, -1.0f)*size);
		points.push_back(glm::vec3(1.0f, 1.0f, -1.0f)*size);
		points.push_back(glm::vec3(1.0f, -1.0f, -1.0f)*size);
		points.push_back(glm::vec3(1.0f, 1.0f, 1.0f)*size);
		points.push_back(glm::vec3(1.0f, -1.0f, 1.0f)*size);
		points.push_back(glm::vec3(1.0f, 1.0f, 1.0f)*size);
		points.push_back(glm::vec3(1.0f, 1.0f, -1.0f)*size);
		points.push_back(glm::vec3(-1.0f, 1.0f, -1.0f)*size);
		points.push_back(glm::vec3(1.0f, 1.0f, 1.0f)*size);
		points.push_back(glm::vec3(-1.0f, 1.0f, -1.0f)*size);
		points.push_back(glm::vec3(-1.0f, 1.0f, 1.0f)*size);
		points.push_back(glm::vec3(1.0f, 1.0f, 1.0f)*size);
		points.push_back(glm::vec3(-1.0f, 1.0f, 1.0f)*size);
		points.push_back(glm::vec3(1.0f, -1.0f, 1.0)*size);
	}

};