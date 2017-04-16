// Intersection class
// Includes a ray, an intersected object, and
// the T value for the ray
#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include "GeoObject.h"

class Intersection {
public:

   void print();

   // Return true if the ray intersects with an object in the scene, 
   // Otherwise return false
   bool hit() { return t != INFINITY; };

   Ray ray;
   GeoObject *object;
   float t;
};

#endif
