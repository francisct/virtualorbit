#include "Shape.h"

#include "Controls.h"
#include "ObjLdr.h"
#include "GLOBALS.h"
#include "World.h"

extern Timer timer;
extern World world;

Shape::Shape() {}

Shape::Shape(glm::vec3 ratio, std::vector<glm::vec3> inV, std::vector<glm::vec2> inU, std::vector<glm::vec3> inN) {
	vertices = inV;

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].x = vertices[i].x * ratio.x;
		vertices[i].y = vertices[i].y * ratio.y;
		vertices[i].z = vertices[i].z * ratio.z;
	}

	uvs = inU;
	normals = inN;
}

Shape::Shape(std::vector<glm::vec3> inV, std::vector<glm::vec2> inU, std::vector<glm::vec3> inN) {
	vertices = inV;
	uvs = inU;
	normals = inN;
}

void Shape::generateMVP() {
	computeMatricesFromInputs();
	model = translation * rotation * scalation;
}

void Shape::passMVPtoShader() {
	generateMVP();
	//registering my matrices to be used in the shaders
	world.cam.passMVPtoShader(&model);
}

void Shape::sendVertices() {

	//setup vbo for vertices
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	if (vertices.size() > 0) {
		//this is to reset the buffer in case there are any changes
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
	}
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void Shape::sendUVs() {

	//setup vbo for uvs
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	if (uvs.size() > 0) {
		//this is to reset the buffer in case there are any changes
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(uvs[0]), &uvs[0], GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
	}
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void Shape::sendNormals() {
	//setup vbo for normals
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	if (normals.size() > 0) {
		//this is to reset the buffer in case there are any changes
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
	}
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void Shape::drawObject() {
	passMVPtoShader();
	world.shadows.sendToShaderForObjectCalculations();
	
	
	sendVertices();
	sendUVs();
	sendNormals();
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
void Shape::drawShadow() {
	if (rotationPending) {
		rotate90(toRotate);
	}
	if (tra.rotateAroundActivated) {
		rotateAround(tra.obj);
	}
	world.shadows.sendToShaderForShadowCalculations(&model, world.light);
	sendVertices();
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
void Shape::setupRotation(float speed) {
	rotationPending = true;
	incrementalRotation = 1;
	toRotate = speed;
	timer.reset();
}

void Shape::resetRotation() {
	rotationPending = false;
	incrementalRotation = 0.0f;
	toRotate = 0.0f;
}

void Shape::rotateBy(float angle) {
	//based on the old rotation matrix I add append my new rotation
	rotation = glm::rotate(rotation, angle, glm::vec3(0, 1, 0));
}
//rotate objects by 90 with an animation
void Shape::rotate90(float speed) {
	if (incrementalRotation == 0) {
		//registering rotation variables
		setupRotation(speed);
	}
	if (incrementalRotation*speed <= ROTATION_90 && incrementalRotation*speed >= -ROTATION_90) {
		if (timer.elapsedTime >= roationTimeLimit) {
			rotation = glm::rotate(rotation, speed, glm::vec3(0, 1, 0));

			incrementalRotation++;
			timer.reset();
		}
	}
	else {
		resetRotation();
	}

}

void Shape::setupRotateAround(Shape *shape) {
	tra.rotateAroundActivated = true;
	tra.obj = shape;
	glm::vec3 xyz = pos - shape->pos;
	tra.r = glm::length(xyz);
	computeInitialPhiAndTheta(shape);
	tra.t = tra.initialT;
	tra.p = tra.initialP;
	tra.toIncrementT = (PI - 2 * tra.initialT) / 50;
	tra.toIncrementP = 2 * PI / 500;
}

void Shape::computeInitialPhiAndTheta(Shape* shape) {
	//the opengl coordinates system is not the same as the cartesian system, therefore I to remap the axis
	float z = -pos.z + shape->pos.z;
	float x = pos.x - shape->pos.x;
	float y = pos.y - shape->pos.y;

	//computing thetha
	tra.initialT = acos(z / tra.r);
	//computing phi
	tra.initialP = atan(y / x);
}

void Shape::rotateAround(Shape *shape) {
	if (!tra.rotateAroundActivated) {
		setupRotateAround(shape);
	}
	//to avoid overflow;
	if (tra.p > 2 * PI + tra.initialP) {
		tra.p = tra.initialP;
	}
	if (tra.t > (PI - tra.initialT)) {
		tra.t -= tra.toIncrementT;
	}
	else {
		tra.t += tra.toIncrementT;
	}


	glm::vec3 newPos;
	tra.p += tra.toIncrementP;
	//tra.t += 0.1;
	newPos.x = tra.r * sin(tra.t) * cos(tra.p);
	newPos.y = tra.r * sin(tra.t) * sin(tra.p);
	newPos.z = tra.r *cos(tra.t);

//I add shape->pos because the reference system for the rotation it the center of shape and not the center of the open glaxis
	glm::vec3 travelTo = newPos - pos + shape->pos;
	
	translate(travelTo);
}

void Shape::translate(glm::vec3 travelTo) {
	//based on the old translation matrix I add append my new translation
	translation = glm::translate(translation, travelTo);
	pos += travelTo;
}

void Shape::scale(glm::vec3 multiplier) {
	scalation = glm::scale(scalation, multiplier);
}

glm::mat4 Shape::swapXandY(const glm::mat4 &toSwap) {
	glm::mat4 isSwapped = glm::mat4(toSwap[0][0], toSwap[0][0], toSwap[0][2], toSwap[0][3],
		toSwap[0][0], toSwap[1][0], toSwap[1][2], toSwap[1][3],
		toSwap[2][0], toSwap[2][0], toSwap[2][2], toSwap[2][3],
		toSwap[3][0], toSwap[3][0], toSwap[3][2], toSwap[3][3]);
	return isSwapped;
}