// Intersection class
// Includes a ray, an intersected object,
// the T value for the ray, and the intersection point
// in world coords
#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include "Scene.hpp"

class Intersection {
public:

   Intersection(Scene*, Ray&);
   
   void print();

   // Return true if the ray intersects with an object in the scene 
   bool hit() { return t != INFINITY; };

   Ray ray;
   GeoObject *object;
   float t;
   glm::vec3 point;
};

#endif
