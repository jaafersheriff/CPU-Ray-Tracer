#include "Triangle.hpp"

Triangle::Triangle() : GeoObject() {
	this->type = "Triangle";

	this->corner1 = glm::vec3(0, 0, 0);
	this->corner2 = glm::vec3(0, 0, 0);
	this->corner3 = glm::vec3(0, 0, 0);
}	


float Triangle::intersect(const Ray &ray) {
	// TODO
	return 0.f;
}

glm::vec3 Triangle::findNormal(const glm::vec3 intersection_point) {
	// TODO
	return glm::vec3(0, 0, 0);
}

void Triangle::print() {
	std::cout << "- Type: Triangle" << std::endl;
	std::cout << "- Corner 1: {";
		std::cout << corner1.x << " " << corner1.y << " " << corner1.z;
		std::cout << "}" << std::endl;
	std::cout << "- Corner 2: {";
		std::cout << corner2.x << " " << corner2.y << " " << corner2.z;
		std::cout << "}" << std::endl;
	std::cout << "- Corner 3: {";
	GeoPrint();
}		
