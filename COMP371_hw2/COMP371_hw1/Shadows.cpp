#include "Shadows.h"

void Shadows::generateIDs(GLuint shaderProgram) {
	depthMatrixID = glGetUniformLocation(shaderProgram, "depthMVP");
}