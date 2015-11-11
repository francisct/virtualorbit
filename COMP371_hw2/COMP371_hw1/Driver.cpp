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
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
#include "World.h"
#include "Cube.h"
#include "Timer.h"
#include "Texture.h"
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


// YOU DO NOT NEED TO CHANGE ANYTHING IN THIS FUNCTION UNLESS YOU ARE DOING THE EXTRA CREDIT
// IN WHICH CASE YOU HAVE TO UNCOMMENT ONE LINE: glBindAttribLocation(ProgramID, 1, "in_Color");
// GIVEN TWO FILENAMES (VERTEX SHADER, FRAGMENT SHADER) IT WILL LOAD THEM
// AND LINK THEM INTO A PROGRAM. THE SHADER PROGRAM ID IS A GLOBAL VARIABLE
// The following code is taken from
// www.opengl-tutorial.org
//
GLuint loadShaders(std::string vertex_shader_path, std::string fragment_shader_path)	{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_shader_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_shader_path.c_str());
		getchar();
		exit(-1);
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_shader_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_shader_path.c_str());
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_shader_path.c_str());
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	
	glBindAttribLocation(ProgramID, 0, "in_Position");
	//Uncomment below for extra credit. You should also uncomment the variable of the same name 
	//appearing in the vertex shader.
	//glBindAttribLocation(ProgramID, 1, "in_Color");

	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	//The three variables below hold the id of each of the variables in the shader
	//If you read the vertex shader file you'll see that the same variable names are used.
	view_matrix_id = glGetUniformLocation(ProgramID, "view_matrix");
	model_matrix_id = glGetUniformLocation(ProgramID, "model_matrix");
	proj_matrix_id = glGetUniformLocation(ProgramID, "proj_matrix");
	

	return ProgramID;
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

int main() {
	///Make sure the size of vec3 is the same as 3 floats
	assert(sizeof(glm::vec3) == sizeof(float) * 3);
	assert(sizeof(glm::uvec3) == sizeof(unsigned int) * 3);

	initialize();

	setCallbacks();
	
	//shader_program = loadShaders("COMP371_hw1.vs", "COMP371_hw1.fs");
    shader_program = loadShaders("lightingAndTexture.vs", "lightingAndTexture.fs");

	timer= Timer();
	world = World();
	//add main platform
	world.addPlayer();
	world.addShape( 10, 0.3, 1, -1);
	world.addShape(3, 0.3, 3, 4);
	vector<GLuint> vaos;
	world.registerVAOS(&vaos);

	loadTexture();
	glUseProgram(shader_program);
	GLuint LightPosID = glGetUniformLocation(shader_program, "LightPosition_worldspace");
	GLuint LightDirID = glGetUniformLocation(shader_program, "LightDirection_cameraspace");
	while (!glfwWindowShouldClose(window)) {
		
		timer.getElapsedTime();

		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

		timer.updateLastTime();
	}

	cleanUp();
	return 0;
}



