#include "Box.h"

using namespace glm;
using namespace std;

Box::Box() {
	this->translate = vec3(0, 0, 0);
	
	this->corner1 = vec3(0, 0, 0);
	this->corner2 = vec3(0, 0, 0);
	this->color = vec3(0, 0, 0);
	this->ambient = 0;
	this->diffuse = 0;
	this->rotate = vec3(0, 0, 0);
}

void Box::print() {
	// TODO
}
