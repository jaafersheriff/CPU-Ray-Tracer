#ifndef _RAY_H_
#define _RAH_H_

#include "glm/glm.hpp"

class Ray {
public:
	Ray();

	void print();

	int pixel_x, pixel_y;
	glm::vec3 direction;
};

#endif
