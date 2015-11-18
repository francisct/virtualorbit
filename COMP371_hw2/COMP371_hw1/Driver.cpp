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
#include "Cube.h"
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

GLuint shader_program = 0;
GLuint Texture;
GLuint TextureID;

GLuint view_matrix_id = 0;
GLuint model_matrix_id = 0;
GLuint proj_matrix_id = 0;

glm::mat4 proj_matrix;
glm::mat4 view_matrix;

///Change the size of the rendered points
GLfloat point_size = 1.0f;

int windowWidth = 640;
int windowHeight = 480;

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
	

	int w, h;
	glfwGetWindowSize(window, &w, &h);
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

	//MVP
	glm::mat4 proj_matrix = getProjectionMatrix();
	glm::mat4 view_matrix = getViewMatrix();

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
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, keypress_callback);
	//glfwSetScrollCallback(window, scroll_callback);
}

void loadTexture() {
	// Load the texture
    Texture = loadDDS("uvmap.DDS");
	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(shader_program, "myTextureSampler");
}

void bindTexture() {
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);
}

void setMVPids(GLuint shaderID) {
	//The three variables below hold the id of each of the variables in the shader
	//If you read the vertex shader file you'll see that the same variable names are used.
	view_matrix_id = glGetUniformLocation(shaderID, "view_matrix");
	model_matrix_id = glGetUniformLocation(shaderID, "model_matrix");
	proj_matrix_id = glGetUniformLocation(shaderID, "proj_matrix");
}

bool test() {
	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	// No color output in the bound framebuffer, only depth.
	glDrawBuffer(GL_NONE);

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;


	// The quad's FBO. Used only for visualizing the shadowmap.
	static const GLfloat g_quad_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,
	};

	GLuint quad_vertexbuffer;
	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	GLuint quad_programID = loadShaders("Passthrough.vertexshader", "SimpleTexture.fragmentshader");
	GLuint texID = glGetUniformLocation(quad_programID, "texture");


	// Create and compile our GLSL program from the shaders
	GLuint programID = loadShaders("ShadowMapping.vertexshader", "ShadowMapping.fragmentshader");
	GLuint depthProgramID = loadShaders("DepthRTT.vertexshader", "DepthRTT.fragmentshader");

	GLuint depthMatrixID = glGetUniformLocation(depthProgramID, "depthMVP");
	GLuint DepthBiasID = glGetUniformLocation(programID, "DepthBiasMVP");
	GLuint ShadowMapID = glGetUniformLocation(programID, "shadowMap");

	// Get a handle for our "LightPosition" uniform
	GLuint lightInvDirID = glGetUniformLocation(programID, "LightInvDirection_worldspace");

}

int main() {

	///Make sure the size of vec3 is the same as 3 floats
	assert(sizeof(glm::vec3) == sizeof(float) * 3);
	assert(sizeof(glm::uvec3) == sizeof(unsigned int) * 3);

	initialize();
	setCallbacks();

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	// No color output in the bound framebuffer, only depth.
	glDrawBuffer(GL_NONE);

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;


	// The quad's FBO. Used only for visualizing the shadowmap.
	static const GLfloat g_quad_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,
	};

	GLuint quad_vertexbuffer;
	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	GLuint quad_programID = loadShaders("Passthrough.vertexshader", "SimpleTexture.fragmentshader");
	GLuint texID = glGetUniformLocation(quad_programID, "texture");


	// Create and compile our GLSL program from the shaders
	GLuint programID = loadShaders("ShadowMapping.vertexshader", "ShadowMapping.fragmentshader");
	GLuint depthProgramID = loadShaders("DepthRTT.vertexshader", "DepthRTT.fragmentshader");

	GLuint depthMatrixID = glGetUniformLocation(depthProgramID, "depthMVP");
	GLuint DepthBiasID = glGetUniformLocation(programID, "DepthBiasMVP");
	GLuint ShadowMapID = glGetUniformLocation(programID, "shadowMap");

	// Get a handle for our "LightPosition" uniform
	GLuint lightInvDirID = glGetUniformLocation(programID, "LightInvDirection_worldspace");































	
	
	//shader_program = loadShaders("COMP371_hw1.vs", "COMP371_hw1.fs");
    //shader_program = loadShaders("lightingAndTexture.vs", "lightingAndTexture.fs");

	setMVPids(programID);
	timer= Timer();
	world = World();
	//add main platform
	world.addPlayer();
	world.addShape( 10, 0.3, 1, 1, -1, 0);
	world.addShape(3, 0.3, 1, 3, 4, 0);
	vector<GLuint> vaos;
	world.registerVAOS(&vaos);

	//loadTexture();
	//glUseProgram(shader_program);
	//GLuint LightPosID = glGetUniformLocation(shader_program, "LightPosition_worldspace");
	//GLuint LightDirID = glGetUniformLocation(shader_program, "LightDirection_cameraspace");
	while (!glfwWindowShouldClose(window)) {
		
		timer.getElapsedTime();







		// Render to our framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glViewport(0, 0, 1024, 1024); // Render on the whole framebuffer, complete from the lower left corner to the upper right

									  // We don't use bias in the shader, but instead we draw back faces, 
									  // which are already separated from the front faces by a small distance 
									  // (if your geometry is made this way)
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

							 // Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(depthProgramID);

		glm::vec3 lightInvDir = glm::vec3(0.5f, 2, 2);

		// Compute the MVP matrix from the light's point of view
		glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
		glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		// or, for spot light :
		//glm::vec3 lightPos(5, 20, 20);
		//glm::mat4 depthProjectionMatrix = glm::perspective<float>(45.0f, 1.0f, 2.0f, 50.0f);
		//glm::mat4 depthViewMatrix = glm::lookAt(lightPos, lightPos-lightInvDir, glm::vec3(0,1,0));

		glm::mat4 depthModelMatrix = glm::mat4(1.0);
		glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);
		world.draw();



		// Render to the screen
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, 1024, 768); // Render on the whole framebuffer, complete from the lower left corner to the upper right

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

							 // Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		//ViewMatrix = glm::lookAt(glm::vec3(14,6,4), glm::vec3(0,1,0), glm::vec3(0,1,0));
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

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

		glUniform3f(lightInvDirID, lightInvDir.x, lightInvDir.y, lightInvDir.z);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		glUniform1i(ShadowMapID, 1);

		world.draw();

		// Optionally render the shadowmap (for debug only)

		// Render only on a corner of the window (or we we won't see the real rendering...)
		glViewport(0, 0, 512, 512);

		// Use our shader
		glUseProgram(quad_programID);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		// Set our "renderedTexture" sampler to user Texture Unit 0
		glUniform1i(texID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		// Draw the triangle !
		// You have to disable GL_COMPARE_R_TO_TEXTURE above in order to see anything !
		//glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles
		glDisableVertexAttribArray(0);


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
























		// wipe the drawing surface clear
		/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPointSize(point_size);
		
		glUseProgram(shader_program);

		//setting and registering light position
		glm::vec3 lightPos = glm::vec3(0, 4, 2);
		glm::vec3 lightDir = glm::vec3(0,-1, 0);
		//glUniform3f(LightPosID, lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(LightPosID, world.player.flashlightPos.x, world.player.flashlightPos.y, world.player.flashlightPos.z);
		glUniform3f(LightDirID, lightDir.x, lightDir.y, lightDir.z);
		//bindTexture();
		world.draw();
		
		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
		*/
		timer.updateLastTime();
	}

	cleanUp();
	return 0;
}



