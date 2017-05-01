#include "Sphere.hpp"

Sphere::Sphere() : GeoObject() {
	this->type = "Sphere";
		
	this->center = glm::vec3(0, 0, 0);
	this->radius = 0;
}

glm::vec3 Sphere::findNormal(const glm::vec3 intersection_point) {
	return glm::normalize(intersection_point - center);
}


float Sphere::intersect(const Ray &ray) {
	glm::vec3 pc = ray.position-center;

	float A = dot(ray.direction, ray.direction);
	float B = dot(ray.direction + ray.direction, pc);
	float C = dot(pc, pc) - radius*radius;

	float det = sqrt(B*B-4*A*C);
	float t1 = (-B+det)/(2*A);
	float t2 = (-B-det)/(2*A);
	
	return t1 < t2 ? t1 : t2;
}

void Sphere::print() {
	std::cout << "- Type: Sphere" << std::endl;
	std::cout << "- Center: {";
		std::cout << center.x << " " << center.y << " " << center.z;
		std::cout << "}" << std::endl;
	std::cout << "- Radius: ";
		std::cout << radius << std::endl;
	std::cout << "- Color: {";
		std::cout << color.x << " " << color.y << " " << color.z;
		std::cout << "}" << std::endl;
	GeoPrint();
}
