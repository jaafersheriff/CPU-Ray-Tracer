#include "Ray.hpp"

Ray::Ray() {
	this->position = glm::vec3(0, 0, 0);
	this->direction = glm::vec3(0, 0, 0);
}

Ray::Ray(glm::vec3 pos, glm::vec3 dir) {
   this->position = glm::vec3(pos);
   this->direction = glm::vec3(dir);
}

glm::vec3 Ray::intersection_point(float t) {
	return position + t * direction;
}

void Ray::print() {
   std::cout << "Ray: {" << position.x << " " << position.y << " " << position.z;
   std::cout << "} -> {" << direction.x << " " << direction.y << " " << direction.z;
   std::cout << "}" << std::endl;
}
