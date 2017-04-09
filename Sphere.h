#pragma once
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "GeoObject.h"

class Sphere: public GeoObject {
public: 
	Sphere();

	void print();

	glm::vec3 center;
	float radius;
	glm::vec3 pigment;
	float ambient;
	float diffuse;
};

#endif
