#pragma once

#include <cmath>

#include "..\glew\glew.h"		// include GL Extension Wrangler
#include "..\glfw\glfw3.h"  
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"
using namespace glm;

#include <vector>
using namespace std;
#include "GLOBALS.h"
#include "Shape.h"
#include "World.h"

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void keypress_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void adjustBasedOnCurvature();
