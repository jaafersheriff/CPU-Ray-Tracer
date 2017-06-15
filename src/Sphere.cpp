#include "Sphere.hpp"
#include <algorithm>
#include <math.h>

#define PI 3.14159265359

Sphere::Sphere() : GeoObject() {
	this->type = "Sphere";

	this->center = glm::vec3(0, 0, 0);
	this->radius = 0;
}

glm::vec3 Sphere::findNormal(glm::vec3 point) {
	return glm::normalize(point - center);
}

glm::vec3 Sphere::findCenter() {
	return center;
}

float Sphere::intersect(const Ray &ray) {
	glm::vec3 pc = ray.position - center;

	const float A = dot(ray.direction, ray.direction);
	const float B = dot(ray.direction + ray.direction, pc);
	const float C = dot(pc, pc) - radius*radius;
	float det = B*B-4*A*C;

	if (det < 0 || !A) {
		return -1;
	}

	det = sqrt(det);
	float t1 = (-B+det)/(2*A);
	float t2 = (-B-det)/(2*A);

	if (t1 > 0 && t2 > 0) {
		return std::min(t1, t2);
	}
	if (t1 > 0) {
		return t1;
	}
	if (t2 > 0) {
		return t2;
	}
	return -1;
}

BoundingBox* Sphere::createBox() {
	glm::vec3 min = this->center;
	glm::vec3 max = this->center;
	for (int axis = 0; axis <= 2; axis++) {
		min[axis] -= radius;
		max[axis] += radius;
	}
	BoundingBox* box = new BoundingBox(min, max);
	box->transform(this->M);
	return box;
}

glm::vec2 Sphere::getUVCoords(glm::vec3 point) {
   glm::vec3 N = findNormal(point);

   float u = glm::asin(N.x)/PI + 0.5f;
   float v = glm::asin(N.y)/PI + 0.5f;

   return glm::vec2(glm::clamp(u, 0.f, 1.f), glm::clamp(v, 0.f, 1.f));
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
