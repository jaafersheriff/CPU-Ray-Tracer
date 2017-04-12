#include "Ray.h"

using namespace glm;

Ray::Ray() {
	this->position = vec3(0, 0, 0);
	this->direction = vec3(0, 0, 0);
}

vec3 Ray::intersection(float t) {
	return position + t * direction;
}

void Ray::print() {
	// TODO
}
