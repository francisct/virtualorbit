// COMP371_hw1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "..\glew\glew.h"		// include GL Extension Wrangler

#include "..\glfw\glfw3.h"  // include GLFW helper library

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"

#include "Controls.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <vector>
#include <string>
#include <algorithm>
using namespace std;
#include "World.h"
#include "Timer.h"
#include "TextureLdr.h"
#include "ShaderLdr.h"
#include "Cam.h"

#define M_PI        3.14159265358979323846264338327950288   /* pi */
#define DEG_TO_RAD	M_PI/180.0f

GLFWwindow* window = 0x00;
int glRenderingType = GL_TRIANGLES;

Timer timer;
World world;

GLuint simpleLightShaders = 0;
GLuint Texture;
GLuint TextureID;


GLuint depthShaders;
GLuint realisticLightShaders;

///Change the size of the rendered points
GLfloat point_size = 1.0f;

int windowWidth = 640;
int windowHeight = 480;

// Get mouse position
double mouseXpos = 0, mouseYpos = 0;

bool initialize() {
	/// Initialize GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return false;
	}

	/// Create a window of size 640x480 and with title "Lecture 2: First Triangle"
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	
	window = glfwCreateWindow(windowWidth, windowHeight, "A1-6615287", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return false;
	}
	
	glfwMakeContextCurrent(window);

	/// Initialize GLEW extension handler
	glewExperimental = GL_TRUE;	///Needed to get the latest version of OpenGL
	glewInit();

	/// Get the current OpenGL version 
	const GLubyte* renderer = glGetString(GL_RENDERER); /// Get renderer string
	const GLubyte* version = glGetString(GL_VERSION); /// Version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	/// Enable the depth test i.e. draw a pixel if it's closer to the viewer
	glEnable(GL_DEPTH_TEST); /// Enable depth-testing
	glDepthFunc(GL_LESS);	/// The type of testing i.e. a smaller value as "closer"

	simpleLightShaders = loadShaders("lightingAndTexture.vs", "lightingAndTexture.fs");
	depthShaders = loadShaders("DepthRTT.vertexshader", "DepthRTT.fragmentshader");
	realisticLightShaders = loadShaders("ShadowMapping.vertexshader", "ShadowMapping.fragmentshader");
	// Set the cursor position for first frame
	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
	return true;
}

bool cleanUp() {
	//Release memory e.g. vao, vbo, etc
	world.destroy();
	glDeleteTextures(1, &TextureID);
	// Close GL context and any other GLFW resources
	glfwTerminate();

	return true;
}

void setCallbacks() {
	glfwSetKeyCallback(window, keypress_callback);
	glfwSetScrollCallback(window, mouseScrollCallback);
	glfwSetCursorPosCallback(window, watchCursorCallback);
	//glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void prepareGL() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



int main() {
	///Make sure the size of vec3 is the same as 3 floats
	assert(sizeof(glm::vec3) == sizeof(float) * 3);
	assert(sizeof(glm::uvec3) == sizeof(unsigned int) * 3);

	initialize();

	setCallbacks();
	
	world = World(realisticLightShaders, depthShaders);
	//world.cam.setMVPids(simpleLightShaders);
	//add main platform
	world.player.shape = new Sphere();
	world.player.shape->translate(glm::vec3(0, 5, 0));
	world.player.shape->rotateBy(-3.14/2);
	world.objects.push_back(new Cube(glm::vec3(10, 0.3, 1)));
	world.objects.push_back(new Cube(glm::vec3(3, 0.3, 1)));
	world.objects.back()->translate(glm::vec3(3, 4, 0));
	

	timer = Timer();
	while (!glfwWindowShouldClose(window)) {
		
		timer.getElapsedTime();

		GLuint *FramebufferName = new GLuint();
		GLuint depthTexture = prepareDepthTexture(FramebufferName);
		
		glBindFramebuffer(GL_FRAMEBUFFER, *FramebufferName);
		glViewport(0, 0, 1024, 1024); 
		prepareGL();

		glUseProgram(depthShaders);
		world.drawShadows();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
		prepareGL();

		glUseProgram(realisticLightShaders);
		world.drawObjects(depthTexture);

		//glViewport(0, 0, 512, 512);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cleanUp();
	return 0;
}



