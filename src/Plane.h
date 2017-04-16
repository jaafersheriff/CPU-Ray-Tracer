#ifndef _PLANE_H_
#define _PLANE_H_

#include "GeoObject.h"

class Plane: public GeoObject {
public:
	Plane();

	void print();
	float intersect(const Ray &);

	glm::vec3 normal;
	float distance;
	float ambient;
	float diffuse;
};

#endif
