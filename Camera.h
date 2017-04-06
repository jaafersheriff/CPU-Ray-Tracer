#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>

class Camera {
public:
	Camera();

	glm::vec3 location;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 lookAt;
};
#endif
