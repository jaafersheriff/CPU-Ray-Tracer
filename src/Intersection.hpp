// Intersection class
// Includes a ray, an intersected object,
// the T value for the ray, and the intersection point
// in world coords
#pragma once
#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include <vector> // vector

#include "GeoObject.hpp"
#include "Scene.hpp"

class Intersection {
public:
   Intersection() {};
   Intersection(Scene &, Ray &, int);

   // Recursive traversal of spatial data structure to find intersection object
   void boxTraversal(Scene::BoxNode *, Ray &);
   // Create intersection w object intersection 
   void createIntersection(std::vector<GeoObject *>, Ray &);
   void createIntersection(GeoObject *, Ray &);

   void print();

   // True if object is intersected, false otherwise
   bool hit;

   // Object intersected and normal at point of intersection
   // Set to nullptr if no object is intersected
   GeoObject *object = nullptr;
   glm::vec3 normal;

   // Ray of intersection in object and world space
   Ray ray;
   Ray objectRay;

   // t value of intersection and intersection point in object and world space
   float t;
   glm::vec3 point;
	glm::vec3 objectPoint;

	// Color of object at a given intersection point
	// Pulled from object pigment or from texture
	glm::vec3 pigment;

};

#endif
