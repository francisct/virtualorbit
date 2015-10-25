#version 330

uniform mat4 view_matrix, model_matrix, proj_matrix;	

layout(location = 0) in  vec3 in_Position;		//Every time this will be a different vertex position
layout(location = 1) in  vec3 in_Color;		//For the extra credit uncomment the variable
out vec3 out_Color;		//For the extra credit uncomment the variable

void main () {
	mat4 CTM = proj_matrix * view_matrix * model_matrix;
	gl_Position = CTM * vec4 (in_Position, 1.0);

	//For the extra credit uncomment the following line. 
	//This line just passes a color value in out_Color to the fragment shader.
	//If you check the fragment shader you'll find an input variable with the same name
	out_Color = in_Color;
};