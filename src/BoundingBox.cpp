#include "BoundingBox.hpp"

BoundingBox::BoundingBox() {
   Box();
}

BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max) {
   updateBox(min, max);
}

void BoundingBox::transform(glm::mat4 &inv_M) {
   // Catch for uninitialized box
   if (!this->hasBeenInit()) {
      return;
   }

   std::vector<glm::vec3> vertices;
  
   // Calculate 8 points
   vertices.push_back(glm::vec3(minCorner.x, minCorner.y, minCorner.z));
   vertices.push_back(glm::vec3(maxCorner.x, minCorner.y, minCorner.z));
   vertices.push_back(glm::vec3(maxCorner.x, minCorner.y, maxCorner.z));
   vertices.push_back(glm::vec3(minCorner.x, minCorner.y, maxCorner.z));
   vertices.push_back(glm::vec3(minCorner.x, maxCorner.y, minCorner.z));
   vertices.push_back(glm::vec3(minCorner.x, maxCorner.y, maxCorner.z));
   vertices.push_back(glm::vec3(maxCorner.x, maxCorner.y, minCorner.z));
   vertices.push_back(glm::vec3(maxCorner.x, maxCorner.y, maxCorner.z));

   // Reset min and max corner
   float inf = std::numeric_limits<float>::max();
   this->minCorner = glm::vec3(inf, inf, inf);
   this->maxCorner = glm::vec3(inf, inf, inf);

   // Transform 8 points
   // Update min and max as we go
   for (int i = 0; i < 8; i++) {
      glm::vec4 t = glm::vec4(vertices[i], 0.f);
      vertices[i] = glm::vec3(inv_M * t);
      addPoint(vertices[i]);
   }

   updateBox(this->minCorner, this->maxCorner);
}


void BoundingBox::addPoint(glm::vec3 point) {
   // Catch for uninitialized box
   if(!this->hasBeenInit()) {
      updateBox(point, point);
      return;
   }

   // Min
   this->minCorner.x = glm::min(this->minCorner.x, point.x);
   this->minCorner.y = glm::min(this->minCorner.y, point.y);
   this->minCorner.z = glm::min(this->minCorner.z, point.z);
   // Max
   this->maxCorner.x = glm::max(this->maxCorner.x, point.x);
   this->maxCorner.y = glm::max(this->maxCorner.y, point.y);
   this->maxCorner.z = glm::max(this->maxCorner.z, point.z);

   updateBox(this->minCorner, this->maxCorner);
}

void BoundingBox::addBox(BoundingBox *box) {
   // If box is uninitialized
   if (!this->hasBeenInit()) {
      updateBox(box->minCorner, box->maxCorner);
      return;
   }
   
   // Min
   this->minCorner.x = glm::min(this->minCorner.x, glm::min(box->maxCorner.x, box->minCorner.x));
   this->minCorner.y = glm::min(this->minCorner.y, glm::min(box->maxCorner.y, box->minCorner.y));
   this->minCorner.z = glm::min(this->minCorner.z, glm::min(box->maxCorner.z, box->minCorner.z));
   // Max
   this->maxCorner.x = glm::max(this->maxCorner.x, glm::max(box->maxCorner.x, box->minCorner.x));
   this->maxCorner.y = glm::max(this->maxCorner.y, glm::max(box->maxCorner.y, box->minCorner.y));
   this->maxCorner.z = glm::max(this->maxCorner.z, glm::max(box->maxCorner.z, box->minCorner.z));

   updateBox(this->minCorner, this->maxCorner);
}