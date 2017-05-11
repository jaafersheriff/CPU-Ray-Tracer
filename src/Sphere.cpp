#include "Sphere.hpp"

#include <algorithm>

Sphere::Sphere() : GeoObject() {
	this->type = "Sphere";

	this->center = glm::vec3(0, 0, 0);
	this->radius = 0;
}

glm::vec3 Sphere::findNormal(const glm::vec3 intersection_point) {
	return glm::normalize(intersection_point - center);
}


float Sphere::intersect(const Ray &ray) {
	glm::vec3 pc = ray.position - center;

	const float A = dot(ray.direction, ray.direction);
	const float B = dot(ray.direction + ray.direction, pc);
	const float C = dot(pc, pc) - radius*radius;
	const float det = sqrt(B*B-4*A*C);

	if (!det || !A) {
		return -1;
	}

	float t1 = (-B+det)/(2*A);
	float t2 = (-B-det)/(2*A);

	return (t1 > 0 && t2 > 0) ? std::min(t1, t2) : (t1 > 0) ? t1 : t2;
}

void Sphere::print() {
	std::cout << "- Type: Sphere" << std::endl;
	std::cout << "- Center: {";
		std::cout << center.x << " " << center.y << " " << center.z;
		std::cout << "}" << std::endl;
	std::cout << "- Radius: ";
		std::cout << radius << std::endl;
	GeoPrint();
}
