// Intersection class
// Includes a ray, an intersected object,
// the T value for the ray, and the intersection point
// in world coords
#pragma once
#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include <vector> // vector

#include "GeoObject.hpp"

class Intersection {
public:
   Intersection() {};
   Intersection(std::vector<GeoObject *>, Ray&);

   void print();

   // Object intersected and normal at point of intersection
   // Set to nullptr if no object is intersected
   GeoObject *object = nullptr;
   glm::vec3 normal;

   // Ray of intersection and transformed ray of intersection
   Ray ray;
   Ray objectRay;
   // t value of intersection, world coords of intersection
   float t;
   glm::vec3 point;

   // True if object is intersected, false otherwise
   bool hit;
};

#endif
