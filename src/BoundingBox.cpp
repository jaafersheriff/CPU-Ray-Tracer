#include "BoundingBox.hpp"

BoundingBox::BoundingBox() {
   Box();
}

BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max) {
   updateBox(min, max);
}

// Bounding box up to this point has been initialized as objects object space
void BoundingBox::transform(glm::mat4 &M) {
   // Catch for uninitialized box
   if (!this->hasBeenInit()) {
      return;
   }

   // Calculate 8 points
   std::vector<glm::vec3> vertices;
   vertices.push_back(glm::vec3(minCorner.x, minCorner.y, minCorner.z));
   vertices.push_back(glm::vec3(minCorner.x, minCorner.y, maxCorner.z));
   vertices.push_back(glm::vec3(minCorner.x, maxCorner.y, minCorner.z));
   vertices.push_back(glm::vec3(minCorner.x, maxCorner.y, maxCorner.z));
   vertices.push_back(glm::vec3(maxCorner.x, minCorner.y, minCorner.z));
   vertices.push_back(glm::vec3(maxCorner.x, minCorner.y, maxCorner.z));
   vertices.push_back(glm::vec3(maxCorner.x, maxCorner.y, minCorner.z));
   vertices.push_back(glm::vec3(maxCorner.x, maxCorner.y, maxCorner.z));

   float inf = std::numeric_limits<float>::max();
   this->minCorner = glm::vec3(inf, inf, inf);
   this->maxCorner = glm::vec3(-inf, -inf, -inf);

   // Transform 8 points
   // Update min and max as we go
   for (int i = 0; i < 8; i++) {
      vertices[i] = glm::vec3(M * glm::vec4(vertices[i], 1.f));
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
   this->minCorner.x = std::min(point.x, std::min(this->minCorner.x, this->maxCorner.x));
   this->minCorner.y = std::min(point.y, std::min(this->minCorner.y, this->maxCorner.y));
   this->minCorner.z = std::min(point.z, std::min(this->minCorner.z, this->maxCorner.z));
   // Max
   this->maxCorner.x = std::max(point.x, std::max(this->minCorner.x, this->maxCorner.x));
   this->maxCorner.y = std::max(point.y, std::max(this->minCorner.y, this->maxCorner.y));
   this->maxCorner.z = std::max(point.z, std::max(this->minCorner.z, this->maxCorner.z));

   updateBox(this->minCorner, this->maxCorner);
}

void BoundingBox::addBox(BoundingBox *box) {
   // If box is uninitialized
   if (!this->hasBeenInit()) {
      updateBox(box->minCorner, box->maxCorner);
      return;
   }
   
   // Min
   this->minCorner.x = std::min(this->minCorner.x, std::min(box->maxCorner.x, box->minCorner.x));
   this->minCorner.y = std::min(this->minCorner.y, std::min(box->maxCorner.y, box->minCorner.y));
   this->minCorner.z = std::min(this->minCorner.z, std::min(box->maxCorner.z, box->minCorner.z));
   // Max
   this->maxCorner.x = std::max(this->maxCorner.x, std::max(box->maxCorner.x, box->minCorner.x));
   this->maxCorner.y = std::max(this->maxCorner.y, std::max(box->maxCorner.y, box->minCorner.y));
   this->maxCorner.z = std::max(this->maxCorner.z, std::max(box->maxCorner.z, box->minCorner.z));

   updateBox(this->minCorner, this->maxCorner);
}