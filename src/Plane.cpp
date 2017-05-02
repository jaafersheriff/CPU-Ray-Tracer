#include "Plane.hpp"

Plane::Plane() : GeoObject() {
	this->type = "Plane";
	
	this->normal = glm::vec3(0, 0, 0);
	this->distance = 0;
}

glm::vec3 Plane::findNormal(const glm::vec3 intersection_point) {
	return normal;
}


float Plane::intersect(const Ray &ray) {
	return (distance - dot(ray.position, normal))/(dot(ray.direction, normal));
}

void Plane::print() {
	std::cout << "- Type: Plane" << std::endl;
	std::cout << "- Normal: {";
		std::cout << normal.x << " " << normal.y << " " << normal.z;
		std::cout << "}" << std::endl;
	std::cout << "- Distance: ";
		std::cout << distance << std::endl;
	GeoPrint();
}
