#pragma once

#include <string>
#include "..\glew\glew.h"		// include GL Extension Wrangler

GLuint loadShaders(std::string vertex_shader_path, std::string fragment_shader_path);

