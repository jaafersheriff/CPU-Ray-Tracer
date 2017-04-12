#ifndef _RAY_H_
#define _RAH_H_

#include "glm/glm.hpp"

class Ray {
public:
	Ray();

	void print();
	glm::vec3 intersection(float);

	glm::vec3 position;
	glm::vec3 direction;
};

#endif
