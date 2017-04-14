#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include "GeoObject.h"

class Intersection {
public:

   void print();
   bool hit() { return t != INFINITY; };

   Ray ray;
   GeoObject *object;
   float t;
};

#endif