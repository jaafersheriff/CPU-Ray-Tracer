#pragma once
#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <glm/glm.hpp>

struct Camera { 
	glm::vec3 location;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 lookAt;
};

struct Light {
	glm::vec3 position;
	glm::vec3 color;
};

struct Sphere {
	glm::vec3 center;
	float radius;
	glm::vec3 pigment;
	glm::vec2 finish;
	glm::vec3 position;
};

struct Plane {
	glm::vec3 normal;
	float distance;
	glm::vec3 pigment;
	glm::vec2 finish;
};

#endif
