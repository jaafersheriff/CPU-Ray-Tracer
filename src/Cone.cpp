#include "Cone.h"

using namespace glm;
using namespace std;

Cone::Cone() {
	this->base = vec3(0, 0, 0);
	this->baseRadius = 0;
	this->cap = vec3(0, 0, 0);
	this->capRadius = 0;
	this->color = vec3(0, 0, 0);
	this->scale = vec3(0, 0, 0);
	this->rotate = vec3(0, 0, 0);
}

void Cone::print() {
	// TODO
}
