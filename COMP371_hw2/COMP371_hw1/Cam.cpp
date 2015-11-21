#include "Cam.h"

Cam::Cam() {}

void Cam::generateIDs(GLuint shaderID) {
	//The three variables below hold the id of each of the variables in the shader
	//If you read the vertex shader file you'll see that the same variable names are used.
	view_matrix_id = glGetUniformLocation(shaderID, "V");
	model_matrix_id = glGetUniformLocation(shaderID, "M");
	proj_matrix_id = glGetUniformLocation(shaderID, "P");
}

void Cam::passMVPtoShader(const glm::mat4 *model) {
	glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(*model));
	glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
}