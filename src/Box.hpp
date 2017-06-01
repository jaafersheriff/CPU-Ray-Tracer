#ifndef _BOX_H_
#define _BOX_H_

#include <glm/glm.hpp>
#include "Ray.hpp"

class Box {
public:
	Box();
	Box(glm::vec3, glm::vec3);

	void updateBox(glm::vec3, glm::vec3);
	void transform(glm::mat4 &);
	float intersect(const Ray &);
	void updateT(const Ray &, float*, float*, int);

	glm::vec3 minCorner, maxCorner;
	glm::vec3 center;
};

#endif
