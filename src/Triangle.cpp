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
	cout << "- Type: Triangle" << endl;
	cout << "- Corner 1: {";
		cout << corner1.x << " " << corner1.y << " " << corner1.z;
		cout << "}" << endl;
	cout << "- Corner 2: {";
		cout << corner2.x << " " corner2.y << " " << corner2.z;
		cout << "}" << endl;
	cout << "- Corner 3: {";
		cout << corner3.x << " " << corner3.y << " " << corner3.z;
		cout << "}" << endl;
	cout << "- Scale: {";
		cout << scale.x << " " << scale.y << " " << scale.z;
		cout << "}" << endl;
	cout << "- Rotate: {";
		cout << rotate.x << " " << rotate.y << " " << rotate.z;
		cout << "}" << endl;
	cout << "- Color: {";
		cout << color.x << " " << color.y << " " << color.z;
		cout << "}" << endl;
	cout << "- Material:" << endl;
		cout << "\t- Ambient: " << ambient << endl;
		cout << "\t- Diffuse: " << diffuse << endl;
	cout << "- Transform:" << endl;
		cout << "\t- Translate: {";
			cout << translate.x << " " << translate.y << " " << translate.z;
			cout << "}" << endl;
}		
