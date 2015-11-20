#include "Cube.h"
#include "World.h"

extern World world;

Cube::Cube():Shape( world.cubeTemplate.vertices, world.cubeTemplate.uvs, world.cubeTemplate.normals) {

}