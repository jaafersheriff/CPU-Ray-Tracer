#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "GeoObject.h"

class Triangle: public GeoObject {
public:
	Triangle();

	void print();

	glm::vec3 vert1;
	glm::vec3 vert2;
	glm::vec3 vert3;
	glm::vec3 scale;
	glm::vec3 rotate;
	glm::vec3 color;
	float ambient;
	float diffuse;
};

#endif
