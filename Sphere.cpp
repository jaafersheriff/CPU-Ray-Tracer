#include "Sphere.h"

using namespace glm;

Sphere::Sphere() {
	this->center = vec3(0, 0, 0);
	this->radius = 0;
	this->position = vec3(0, 0, 0);
	this->pigment = vec3(0, 0, 0);
	this->ambient = 0;
	this->diffuse = 0;
}
