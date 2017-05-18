// Camera class
// Only functionality is storing data and print
#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>	// vec3
#include <iostream>	// std::cout

class Camera {
public:
	Camera();
	void print();

	glm::vec3 location;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 lookAt;
};

#endif
