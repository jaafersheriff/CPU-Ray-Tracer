#ifndef _CONE_H_
#define _CONE_H_

#include "GeoObject.h"

class Cone: public GeoObject {
public:
	Cone();

	void print();

	glm::vec3 base;
	float baseRadius;
	glm::vec3 cap;
	float capRadius;
	glm::vec3 scale;
	glm::vec3 rotate;
};

#endif
