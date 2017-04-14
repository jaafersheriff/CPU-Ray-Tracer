#include "Plane.h"

using namespace glm;
using namespace std;

Plane::Plane() {
	this->type = "Plane";
	
	this->translate = vec3(0, 0, 0);
	this->color = vec3(0, 0, 0);

	this->normal = vec3(0, 0, 0);
	this->distance = 0;
	this->ambient = 0;
	this->diffuse = 0;
}

float Plane::intersect(Ray &ray) {
	float num = distance - dot(ray.position, normal);
	float den = dot(ray.direction, normal);
	return num/den;
}

void Plane::print() {
	cout << "- Type: Plane" << endl;
	cout << "- Normal: {";
		cout << normal.x << " " << normal.y << " " << normal.z;
		cout << "}" << endl;
	cout << "- Distance: ";
		cout << distance << endl;
	cout << "- Color: {";
		cout << color.x << " " << color.y << " " << color.z;
		cout << "}" << endl;	
	cout << "- Material:" << endl;
		cout << "  - Ambient: ";
			cout << ambient << endl;
		cout << "  - Diffuse: ";
			cout << diffuse << endl;
/*	cout << "- Transform:" << endl;
		cout << "  - Translate: {";
			cout << translate.x << " " << translate.y << " " << translate.z;
		cout << "}" << endl;
*/
}
