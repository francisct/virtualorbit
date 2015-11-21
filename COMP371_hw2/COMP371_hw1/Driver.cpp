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

	// Get a handle for our "MVP" uniform
	// Get a handle for our "MVP" uniform
	GLuint DepthBiasID = glGetUniformLocation(realisticLightShaders, "DepthBiasMVP");
	GLuint ShadowMapID = glGetUniformLocation(realisticLightShaders, "shadowMap");


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
		// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
		GLuint depthTexture = prepareDepthTexture();

		//glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glViewport(0, 0, 1024, 1024); 
		prepareGL();
		glUseProgram(depthShaders);

		glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
		glm::mat4 depthViewMatrix = glm::lookAt(world.light.pos, glm::vec3(-1, -1, 0), glm::vec3(0, 1, 0));

		glm::mat4 depthModelMatrix = glm::mat4(1.0);
		glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(world.shadows.depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);

		world.drawShadows();

		// Render to the screen
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
		prepareGL();
		glUseProgram(realisticLightShaders);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		//ViewMatrix = glm::lookAt(glm::vec3(14,6,4), glm::vec3(0,1,0), glm::vec3(0,1,0));
		glm::mat4 ModelMatrix = glm::mat4(1.0);

		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
			);

		glm::mat4 depthBiasMVP = biasMatrix*depthMVP;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		
		glUniformMatrix4fv(DepthBiasID, 1, GL_FALSE, &depthBiasMVP[0][0]);

		glUniform3f(world.light.lightPosID, world.light.pos.x, world.light.pos.y, world.light.pos.z);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		glUniform1i(ShadowMapID, 1);

		world.drawObjects();

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glViewport(0, 0, 512, 512);

		glDisableVertexAttribArray(0);


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cleanUp();
	return 0;
}



