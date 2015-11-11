
#include "Cube.h"

std::vector<glm::vec3> points;

	Cube::Cube(){}

	Cube::Cube(float size, float width, float height, glm::vec3 position) {
		points.push_back(glm::vec3(-1.0f*width+position.x, -1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, -1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, 1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, 1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, -1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, 1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, -1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, -1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, -1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, 1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, -1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, -1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, -1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, -1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, 1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, 1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, -1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, -1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, -1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, 1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, -1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, -1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, 1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, -1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, 1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, -1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, 1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, -1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, 1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, 1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, 1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, 1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, 1.0f*height+position.y, -1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, 1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, 1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(-1.0f*width+position.x, 1.0f*height+position.y, 1.0f+position.z)*size);
		points.push_back(glm::vec3(1.0f*width+position.x, -1.0f*height+position.y, 1.0+position.z)*size);
	}
