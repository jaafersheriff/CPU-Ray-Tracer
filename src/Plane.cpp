#include "Plane.hpp"

using namespace glm;
using namespace std;

Plane::Plane() {
	this->type = "Plane";

	this->translate = vec3(0, 0, 0);
	this->color = vec3(0, 0, 0);
	this->ambient = 0;
	this->diffuse = 0;
	this->specular = 0;
	this->shininess = 1;
	this->roughness = 0;
	
	this->normal = vec3(0, 0, 0);
	this->distance = 0;
}

vec3 Plane::findNormal(const vec3 intersection_point) {
	return normal;
}


float Plane::intersect(const Ray &ray) {
	return (distance - dot(ray.position, normal))/(dot(ray.direction, normal));
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
}
