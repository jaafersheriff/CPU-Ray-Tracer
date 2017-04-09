#pragma once
#ifndef _GEOOBJECT_H_
#define _GEOOBJECT_H_

#include <iostream>	// cout

#include <glm/glm.hpp>	// vec3

class GeoObject {
public:
	GeoObject() {};

	virtual void print() = 0;

	glm::vec3 translate;
};

#endif
