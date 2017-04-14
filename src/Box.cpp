#include "Box.h"

using namespace glm;
using namespace std;

Box::Box() {
	this->type = "Box";
	
	this->translate = vec3(0, 0, 0);
	this->color = vec3(0, 0, 0);
	
	this->corner1 = vec3(0, 0, 0);
	this->corner2 = vec3(0, 0, 0);
	this->ambient = 0;
	this->diffuse = 0;
	this->rotate = vec3(0, 0, 0);
}

void Box::print() {
	cout << "- Type: Box" << endl;
	cout << "- Corner 1: {";
		cout << corner1.x << " " << corner1.y << " " << corner1.z;
		cout << "}" << endl;
	cout << "- Corner 2: {";
		cout << corner2.x << " " << corner2.y << " " << corner2.z;
		cout << "}" << endl;
	cout << "- Color: {";
		cout << color.x << " " << color.y << " " << color.z;
		cout << "}" << endl;
	cout << "- Material: " << endl;
		cout << "\t- Ambient: ";
			cout << ambient << endl;
		cout << "\t- Diffuse: ";
			cout << diffuse << endl;
	cout << "- Transform:" << endl;
		cout << "\t-Translate {";
			cout << translate.x << " " << translate.y << " " << translate.z;
			cout << "}" << endl;
}
