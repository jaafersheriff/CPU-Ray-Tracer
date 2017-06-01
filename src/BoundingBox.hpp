// Bounding box class
// Implements Box class
// Includes a list of objects witihn this bounding box

#pragma once
#ifndef _BOUNDING_BOX_H_
#define _BOUNDING_BOX_H_

#include <vector>

#include "Box.hpp"

class BoundingBox : public Box {
public:
   BoundingBox();
   BoundingBox(glm::vec3, glm::vec3);

   void addPoint(glm::vec3);
   void addBox(BoundingBox *);
   void transform(glm::mat4 &);
};

#endif