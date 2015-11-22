#include "Cube.h"
#include "World.h"

extern World world;

Cube::Cube() :Shape(world.cubeTemplate.vertices, world.cubeTemplate.uvs, world.cubeTemplate.normals) {}

Cube::Cube(glm::vec3 ratio):Shape(ratio, world.cubeTemplate.vertices, world.cubeTemplate.uvs, world.cubeTemplate.normals) {

}