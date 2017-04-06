#include "Camera.h"

using namespace glm;

Camera::Camera() {
	this->location = vec3(0, 0, 0);
	this->up = vec3(0, 0, 0);
	this->right = vec3(0, 0, 0);
	this->lookAt = vec3(0, 0, 0);
}
