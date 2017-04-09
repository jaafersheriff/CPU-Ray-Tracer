#include "Sphere.h"

using namespace glm;
using namespace std;

Sphere::Sphere() {
	this->translate = vec3(0, 0, 0);

	this->center = vec3(0, 0, 0);
	this->radius = 0;
	this->pigment = vec3(0, 0, 0);
	this->ambient = 0;
	this->diffuse = 0;
}

void Sphere::print() {
	cout << "- Type: Sphere" << endl;
	cout << "- Center: {";
		cout << center.x << " " << center.y << " " << center.z;
		cout << "}" << endl;
	cout << "- Radius: ";
		cout << radius << endl;
	cout << "- Color: {";
		cout << pigment.x << " " << pigment.y << " " << pigment.z;
		cout << "}" << endl;
	cout << "- Material:" << endl;
		cout << "\t- Ambient: ";
			cout << ambient << endl;
		cout << "\t- Diffuse: ";
			cout << diffuse << endl;
	cout << "- Transform:" << endl;
		cout << "\t- Translate: {"; 
			cout << translate.x << " " << translate.y << " " << translate.z;
			cout << "}" << endl;
}
