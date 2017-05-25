// Ray class

#pragma once
#ifndef _RAY_H_
#define _RAH_H_

#include <iostream>  // cout
#include "glm/glm.hpp"

class Ray {
public:
   Ray();
   Ray(glm::vec3, glm::vec3);
   void set(const glm::vec3, const glm::vec3);

   glm::vec3 position;
   glm::vec3 direction;

   // Calculates the point of intersection given a value t
   glm::vec3 calculatePoint(float);

   void print();
};

#endif
