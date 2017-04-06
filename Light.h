#pragma once
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <glm/glm.hpp>

class Light {
public: 
	Light();
	
	glm::vec3 position;
	glm::vec3 color;
};

#endif
