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

   void updateBox(glm::vec3, glm::vec3);

   float intersect(const Ray &);
   glm::vec2 getUVCoords(glm::vec3);
   glm::vec3 findNormal(glm::vec3);
   glm::vec3 findCenter();
   BoundingBox *createBox();
   void print();
};

#endif
