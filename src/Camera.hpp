#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>	// vec3
#include <iostream>	// print
#include <iomanip>	// setprecision
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
