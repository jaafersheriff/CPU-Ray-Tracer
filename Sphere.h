#pragma once
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <glm/glm.hpp>

class Sphere {
public: 
	Sphere();

	glm::vec3 center;
	float radius;
	glm::vec3 position;
	glm::vec3 pigment;
	float ambient;
	float diffuse;
};

#endif
