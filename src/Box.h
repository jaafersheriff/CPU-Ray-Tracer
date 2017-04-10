#pragma once
#ifndef _BOX_H_
#define _BOX_H_

#include "GeoObject.h"

class Box: public GeoObject {
public:
	Box();

	void print();

	glm::vec3 corner1, corner2;
	glm::vec3 color;
	float ambient, diffuse;
	glm::vec3 rotate;
};

#endif
