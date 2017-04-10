#include "Triangle.h"

using namespace glm;
using namespace std;

Triangle::Triangle() {
	this->vert1 = vec3(0, 0, 0);
	this->vert2 = vec3(0, 0, 0);
	this->vert3 = vec3(0, 0, 0);
	this->scale = vec3(0, 0, 0);
	this->rotate = vec3(0, 0, 0);
	this->color = vec3(0, 0, 0);
	ambient = 0;
	diffuse = 0;
}	

void Triangle::print() {
	// TODO
}	
	
