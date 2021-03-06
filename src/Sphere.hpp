// Sphere class extends GeoObject

#pragma once
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "GeoObject.hpp"

class Sphere: public GeoObject {
public:
   Sphere();

   glm::vec3 center;
   float radius;

   float intersect(const Ray &);
   glm::vec2 getUVCoords(glm::vec3);
   glm::vec3 findNormal(glm::vec3);
   glm::vec3 findCenter();
   BoundingBox* createBox();
   void print();
};

#endif
