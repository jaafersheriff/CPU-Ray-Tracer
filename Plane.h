#pragma once
#ifndef _PLANE_H_
#define _PLANE_H_

#include <glm/glm.hpp>

class Plane {
public:
	Plane();

	glm::vec3 normal;
	float distance;
	glm::vec3 pigment;
	float ambient;
	float diffuse;
};

#endif
