#include "Controls.h"
#include "Player.h"


extern GLFWwindow* window;
extern Timer timer;
extern int windowWidth;
extern int windowHeight;
extern GLuint currentShader, realisticLightShader, simpleLightShader;
extern bool shaderHasToggled;

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

		case GLFW_KEY_F:
			toggleShader();
			break;
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
		case GLFW_KEY_K:
			world.cam.direction += glm::vec3(-0.1,0,0);
			break;
		case GLFW_KEY_L:
			world.cam.direction += glm::vec3(0.1, 0, 0);
			break;
		case GLFW_KEY_O:
			world.objects.push_back(new Cube(glm::vec3(10, 0.3, 10)));
			world.objects.back()->translate(glm::vec3(0, 10, 0));
			break;
		}

	
}

void computeMatricesFromInputs() {
	float ar = (float)windowWidth / (float)windowHeight;
	world.cam.ProjectionMatrix = glm::perspective(world.cam.initialFoV, ar, 0.1f, 1000.0f);// Camera matrix

	world.cam.ViewMatrix = lookAt(
		world.cam.position,           // Camera is here
		world.cam.position + world.cam.direction,
		vec3(0, 1, 0)         // Head is up (set to 0,-1,0 to look upside-down)
		);
	glViewport(0, 0, windowWidth, windowHeight);
}

void watchCursorCallback(GLFWwindow *window, double xpos, double ypos) {
	float xCoordPos = xpos - windowWidth / 2;
	float yCoordPos = (windowHeight / 2) - ypos;
	//dividing by 30 approximate the world.cam.position in object space
	world.light.translate (vec3(xCoordPos/20 - world.light.pos.x, yCoordPos/20 - world.light.pos.y, 0));
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

void toggleShader() {

	//I use timer to prevent undesired multiple key press
	if (timer.keyUnpressedTime > 0.1) {
		if (shaderHasToggled == false) {
			if (currentShader == simpleLightShader) {
				currentShader = realisticLightShader;
			}
			else {
				currentShader = simpleLightShader;
			}
			shaderHasToggled = true;
		}
		timer.keyUnpressedTime = 0;
	}
}