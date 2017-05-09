// Intersection class
// Includes a ray, an intersected object,
// the T value for the ray, and the intersection point
// in world coords
#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include <vector>
#include <limits>

#include "GeoObject.hpp"

class Intersection {
public:

   Intersection(std::vector<GeoObject *>, Ray&);

   void print();

   GeoObject *object;
   Ray ray;
   float t;
   glm::vec3 point;
   bool hit;
};

#endif
