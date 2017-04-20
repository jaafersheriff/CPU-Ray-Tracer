#ifndef _PLANE_H_
#define _PLANE_H_

#include "GeoObject.hpp"

class Plane: public GeoObject {
public:
	Plane();

	void print();
	float intersect(const Ray &);
   glm::vec3 findNormal(const glm::vec3 intersection_point);

	glm::vec3 normal;
	float distance;
};

#endif
