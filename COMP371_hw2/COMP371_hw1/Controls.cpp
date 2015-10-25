#include <cmath>

#include "..\glew\glew.h"		// include GL Extension Wrangler

#include "..\glfw\glfw3.h"  
extern GLFWwindow* window;
extern int glRenderingType;


#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"
using namespace glm;

#include "Controls.hpp"
#include <vector>
using namespace std;

#include "Cube.cpp"

mat4 ViewMatrix;
mat4 ProjectionMatrix;

float initialFoV = 45.0f;

mat4 getViewMatrix() {
	return ViewMatrix;
}
mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}

extern vector<vec3> vertices;

vec3 position = vec3(0, 0, 15);
extern int windowWidth;
extern int windowHeight;

extern Cube world;
extern Cube player;

vec3 upDirection = vec3{ 0.0f, 2.0f, 0.0f };
vec3 rightDirection = vec3{ 2.0f, 0.0f, 0.0f };
vec3 zoomDirection = vec3{ 0.0f, 0.0f, 2.0f };


float toDeg(float inRad) {
	return (inRad * 360) / (2 * 3.14159265358979323846264338327950288);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		GLfloat realWidth = (GLfloat)(xpos - windowWidth / 2);
		GLfloat realHeight = (GLfloat)(windowHeight / 2 - ypos);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}

void keypress_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {

		case GLFW_KEY_ENTER:
			glRenderingType = GL_LINE_STRIP;
			break;
		case GLFW_KEY_BACKSPACE:
			break;
		case GLFW_KEY_L:
			glRenderingType = GL_LINE_STRIP;
			break;
		case GLFW_KEY_P:
			glRenderingType = GL_POINTS;
			break;
		case GLFW_KEY_UP:
			position += upDirection;
			break;
		case GLFW_KEY_DOWN:
			position -= upDirection;
			break;
		case GLFW_KEY_RIGHT:
			position += rightDirection;
			break;
		case GLFW_KEY_LEFT:
			position -= rightDirection;
			break;
		case GLFW_KEY_E:
			position -= zoomDirection;
			break;
		case GLFW_KEY_Q:
			position += zoomDirection;
			break;
		case GLFW_KEY_Z:
			world.rotateLeft();
			player.rotateLeft();
			break;
		case GLFW_KEY_X:
			world.rotateRight();
			player.rotateRight();
			break;
		case GLFW_KEY_W:
			player.goUp();
			break;
		case GLFW_KEY_S:
			player.goDown();
			break;
		case GLFW_KEY_A:
			player.goLeft();
			break;
		case GLFW_KEY_D:
			player.goRight();
			break;
		}

	}
}

void computeMatricesFromInputs() {
	float ar = (float)windowWidth / (float)windowHeight;
	ProjectionMatrix = glm::perspective(initialFoV, ar, 0.1f, 1000.0f);// Camera matrix

	ViewMatrix = lookAt(
		position,           // Camera is here
		position + vec3(0.0f, 0.0f, -1.0f),
		vec3(0, 1, 0)         // Head is up (set to 0,-1,0 to look upside-down)
		);
	glViewport(0, 0, windowWidth, windowHeight);
}
