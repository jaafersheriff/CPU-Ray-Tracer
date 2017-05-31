// Plane class extends GeoObject

#pragma once
#ifndef _PLANE_H_
#define _PLANE_H_

#include "GeoObject.hpp"

class Plane: public GeoObject {
public:
   Plane();

   glm::vec3 normal;
   float distance;

   float intersect(const Ray &);
   glm::vec3 findNormal(Ray &, float);
   BoundingBox* createBox();
   void print();
};

#endif
