#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void keypress_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void adjustBasedOnCurvature();

#endif