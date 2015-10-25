
#version 330

in vec3 out_Color;		//For extra credit, this is the input color from the vertex shader. Uncomment.
out vec4 frag_colour;	//This is the final output color used to render the point

void main () {

	//For extra credit: uncomment the following line and remove the last line
	//frag_colour = vec4 (out_Color, 1.0);

	//Set the fragment's color as white. You need to change this or.
	frag_colour = vec4(1.0,1.0,1.0,1.0);
};