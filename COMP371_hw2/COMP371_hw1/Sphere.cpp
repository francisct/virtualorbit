#include "Sphere.h"
#include "World.h"

extern World world;

Sphere::Sphere():Shape( world.sphereTemplate.vertices, world.sphereTemplate.uvs, world.sphereTemplate.normals) {

}