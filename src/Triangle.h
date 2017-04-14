#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "GeoObject.h"

class Triangle: public GeoObject {
public:
	Triangle();

	
	void print();

	glm::vec3 corner1;
	glm::vec3 corner2;
	glm::vec3 corner3;
	glm::vec3 scale;
	glm::vec3 rotate;
	float ambient;
	float diffuse;
};

#endif
