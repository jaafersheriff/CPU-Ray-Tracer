#include "Light.h"

using namespace glm;
using namespace std;

Light::Light() {
	this->position = vec3(0, 0, 0);
	this->color = vec3(0, 0, 0);
}

void Light::print() {
		cout << "- Location: {";
			cout << position.x << " " << position.y << " " << position.z;
			cout << "}" << endl;
		cout << "- Color: {";
			cout << color.x << " " << color.y << " " << color.z;
			cout << "}" << endl;
}
