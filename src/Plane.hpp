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
   glm::vec3 findNormal(const glm::vec3 intersection_point);
   BoundingBox* createBox();
   void print();
};

#endif
