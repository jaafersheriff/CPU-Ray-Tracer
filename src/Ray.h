#ifndef _RAY_H_
#define _RAH_H_

#include <iostream>  // cout
#include "glm/glm.hpp"

class Ray {
public:
	Ray();

	void print();
   glm::vec3 intersection_point(float);

	glm::vec3 position;
	glm::vec3 direction;
};

#endif
