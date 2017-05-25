#include "Ray.hpp"

Ray::Ray() {
	this->position = glm::vec3(0, 0, 0);
	this->direction = glm::vec3(0, 0, 0);
}

Ray::Ray(glm::vec3 pos, glm::vec3 dir) {
	this->position = pos;
	this->direction = dir;
}

void Ray::set(const glm::vec3 p, const glm::vec3 d) {
	this->position = glm::vec3(p);
	this->direction = glm::vec3(d);
}

glm::vec3 Ray::calculatePoint(float t) {
	return position + t * direction;
}

void Ray::print() {
	std::cout << "{" << position.x << " " << position.y << " " << position.z;
	std::cout << "} -> {" << direction.x << " " << direction.y << " " << direction.z;
	std::cout << "}" << std::endl;
}
