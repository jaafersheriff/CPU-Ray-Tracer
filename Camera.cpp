#include "Camera.h"

using namespace std;
using namespace glm;

Camera::Camera() {
	this->location = vec3(0, 0, 0);
	this->up = vec3(0, 0, 0);
	this->right = vec3(0, 0, 0);
	this->lookAt = vec3(0, 0, 0);
}

void Camera::print() {
	cout << "Camera: " << endl;
	cout << "- Location: {";
		cout << location.x << " " << location.y << " " << location.z;
		cout << "}" << endl;
	cout << "- Up: {";
		cout << up.x << " " << up.y << " " << up.z;
		cout << "}" << endl;
	cout << "- Right: {";
		cout << right.x << " " << right.y << " " << right.z;
		cout << "}" << endl;
	cout << "- Look at: {";
		cout << lookAt.x << " " << lookAt.y << " " << lookAt.z;
		cout << "}" << endl;
}
