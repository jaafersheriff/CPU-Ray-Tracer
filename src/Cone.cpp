#include "Cone.h"

using namespace glm;
using namespace std;

Cone::Cone() {
	this->type = "Cone";
	this->color = vec3(0, 0, 0);

	this->base = vec3(0, 0, 0);
	this->baseRadius = 0;
	this->cap = vec3(0, 0, 0);
	this->capRadius = 0;
	this->scale = vec3(0, 0, 0);
	this->rotate = vec3(0, 0, 0);
}

void Cone::print() {
	cout << "- Type: Cone" << endl;
	cout << "- Base: {";
		cout << base.x << " " << base.y << " " << base.z;
		cout << "}" << endl;
	cout << "- Base Radius: " << baseRadius << endl;
	cout << "- Cap: {";
		cout << cap.x << " " << cap.y << " " << cap.z;
		cout << "}" << endl;
	cout << "- Cap Radius: " << capRadius << endl;
	cout << "- Color: {";
		cout << color.x << " " << color.y << " " << color.z;
		cout << "}" << endl;
	cout << "- Scale: {";
		cout << scale.x << " " << scale.y << " " << scale.z;
		cout << "}" << endl;
	cout << "- Rotate: {";
		cout << rotate.x << " " << rotate.y << " " << rotate.z;
		cout << "}" << endl;
	cout << "- Transform:" << endl;
		cout << "\t- Translate: {";
			cout << translate.x << " " << translate.y << " " << translate.z;
			cout << "}" << endl;
}
