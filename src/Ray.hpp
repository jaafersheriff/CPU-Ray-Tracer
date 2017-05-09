#ifndef _RAY_H_
#define _RAH_H_

#include <iostream>  // cout
#include "glm/glm.hpp"

class Ray {
public:
	Ray();
   Ray(glm::vec3 position, glm::vec3 direction);

   void set(const glm::vec3, const glm::vec3);
	void print();
   glm::vec3 calculatePoint(float);

	glm::vec3 position;
	glm::vec3 direction;
};

#endif
