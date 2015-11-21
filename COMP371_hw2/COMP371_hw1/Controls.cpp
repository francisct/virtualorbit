#include "Controls.h"
#include "Player.h"


extern GLFWwindow* window;

extern int windowWidth;
extern int windowHeight;

extern double mouseXpos, mouseYpos;

extern World world;

vec3 upDirection = vec3{ 0.0f, 2.0f, 0.0f };
vec3 rightDirection = vec3{ 2.0f, 0.0f, 0.0f };
vec3 zoomDirection = vec3{ 0.0f, 0.0f, 2.0f };


float toDeg(float inRad) {
	return (inRad * 360) / (2 * 3.14159265358979323846264338327950288);
}

void keypress_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
		switch (key) {

		
		case GLFW_KEY_UP:
			world.cam.position += upDirection;
			break;
		case GLFW_KEY_DOWN:
			world.cam.position -= upDirection;
			break;
		case GLFW_KEY_RIGHT:
			world.cam.position += rightDirection;
			break;
		case GLFW_KEY_LEFT:
			world.cam.position -= rightDirection;
			break;
		case GLFW_KEY_E:
			world.cam.position -= zoomDirection;
			break;
		case GLFW_KEY_Q:
			world.cam.position += zoomDirection;
			break;
		case GLFW_KEY_Z:
			world.rotateWorld(ROTATE_LEFT);
			break;
		case GLFW_KEY_X:
			world.rotateWorld(ROTATE_RIGHT);
			break;
		case GLFW_KEY_W:
			world.player.shape->translate(TRANSLATE_UP);
			break;
		case GLFW_KEY_S:
			world.player.shape->translate(TRANSLATE_DOWN);
			break;
		case GLFW_KEY_A:
			world.player.shape->translate(TRANSLATE_LEFT);
			break;
		case GLFW_KEY_D:
			world.player.shape->translate(TRANSLATE_RIGHT);
			break;
		}

	
}

void computeMatricesFromInputs() {
	float ar = (float)windowWidth / (float)windowHeight;
	world.cam.ProjectionMatrix = glm::perspective(world.cam.initialFoV, ar, 0.1f, 1000.0f);// Camera matrix

	world.cam.ViewMatrix = lookAt(
		world.cam.position,           // Camera is here
		world.cam.position + vec3(0.0f, 0.0f, -1.0f),
		vec3(0, 1, 0)         // Head is up (set to 0,-1,0 to look upside-down)
		);
	glViewport(0, 0, windowWidth, windowHeight);
}

void watchCursorCallback(GLFWwindow *window, double xpos, double ypos) {
	float xCoordPos = xpos - windowWidth / 2;
	float yCoordPos = (windowHeight / 2) - ypos;
	//dividing by 30 approximate the world.cam.position in object space
	world.light.pos = vec3(xCoordPos/30 + world.cam.position.x, yCoordPos/30 + world.cam.position.y, world.light.pos.z);
}

void mouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
	if (yoffset > 0) {
		world.light.pos += glm::vec3( 0, 0, -0.5);
	}
	else {
		world.light.pos += glm::vec3(0, 0, 0.5);
	}
}

void mouseButtonCallback() {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		world.generateShapeOnClickCallback(new Cube());
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		world.generateShapeOnClickCallback(new Sphere());
	}
}
