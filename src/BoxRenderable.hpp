// Renderable box
// Implements Box and GeoObject

#pragma once
#ifndef _BOX_RENDERABLE_H_
#define _BOX_RENDERABLE_H_

#include "GeoObject.hpp"
#include "Box.hpp"

class BoxRenderable : public GeoObject, Box {
public:
   BoxRenderable();

   float intersect(const Ray &);
   glm::vec3 findNormal(const glm::vec3);
   BoundingBox *createBox();
   void print();
};

#endif