// Light class
// Solely holds light data

#pragma once
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <glm/glm.hpp>	// vec3
#include <iostream>	// print

class Light {
public:
   Light();
   void print();

   glm::vec3 position;
   glm::vec3 color;
};

#endif
