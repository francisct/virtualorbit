#include "Controls.h"
#include "Player.h"


extern GLFWwindow* window;
extern int glRenderingType;

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

extern World world;


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
			world.rotateWorld(ROTATE_LEFT);
			break;
		case GLFW_KEY_X:
			world.rotateWorld(ROTATE_RIGHT);
			break;
		case GLFW_KEY_W:
			world.player.translate(TRANSLATE_UP);
			break;
		case GLFW_KEY_S:
			world.player.translate(TRANSLATE_DOWN);
			break;
		case GLFW_KEY_A:
			world.player.translate(TRANSLATE_LEFT);
			break;
		case GLFW_KEY_D:
			world.player.translate(TRANSLATE_RIGHT);
			break;
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