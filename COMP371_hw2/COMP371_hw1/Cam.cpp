#include "Cam.h"

Cam::Cam() {}

void Cam::setMVPids(GLuint shaderID) {
	//The three variables below hold the id of each of the variables in the shader
	//If you read the vertex shader file you'll see that the same variable names are used.
	view_matrix_id = glGetUniformLocation(shaderID, "view_matrix");
	model_matrix_id = glGetUniformLocation(shaderID, "model_matrix");
	proj_matrix_id = glGetUniformLocation(shaderID, "proj_matrix");
}

void Cam::passMVPtoShader(const glm::mat4 *model) {
	glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
	glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(*model));
}