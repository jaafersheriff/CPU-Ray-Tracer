#include "Plane.h"

using namespace glm;
using namespace std;

Plane::Plane() {
	this->translate = vec3(0, 0, 0);

	this->normal = vec3(0, 0, 0);
	this->distance = 0;
	this->pigment = vec3(0, 0, 0);
	this->ambient = 0;
	this->diffuse = 0;
}

float Plane::intersect(Ray &ray) {
	return (distance-dot(ray.position, normal))/dot(ray.direction, normal);
}

void Plane::print() {
	cout << "- Type: Plane" << endl;
	cout << "- Normal: {";
		cout << normal.x << " " << normal.y << " " << normal.z;
		cout << "}" << endl;
	cout << "- Distance: ";
		cout << distance << endl;
	cout << "- Color: {";
		cout << pigment.x << " " << pigment.y << " " << pigment.z;
		cout << "}" << endl;	
	cout << "- Material:" << endl;
		cout << "\t- Ambient: ";
			cout << ambient << endl;
		cout << "\t- Diffuse: ";
			cout << diffuse << endl;
	cout << "- Transform:" << endl;
		cout << "\t Translate: {";
			cout << translate.x << " " << translate.y << " " << translate.z;
		cout << "}" << endl;
}
