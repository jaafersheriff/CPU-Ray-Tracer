#include "Plane.h"

using namespace glm;

Plane::Plane() {
	this->normal = vec3(0, 0, 0);
	this->distance = 0;
	this->pigment = vec3(0, 0, 0);
	this->ambient = 0;
	this->diffuse = 0;
}
