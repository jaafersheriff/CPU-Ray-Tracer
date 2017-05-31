#include "BoundingBox.hpp"

BoundingBox::BoundingBox() {
   Box();
}

BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max) {
   updateBox(min, max);
}

void BoundingBox::addPoint(glm::vec3 point) {
   // Min
   this->minCorner.x = glm::min(this->minCorner.x, point.x);
   this->minCorner.y = glm::min(this->minCorner.y, point.y);
   this->minCorner.z = glm::min(this->minCorner.z, point.z);
   // Max
   this->maxCorner.x = glm::max(this->maxCorner.x, point.x);
   this->maxCorner.y = glm::max(this->maxCorner.y, point.y);
   this->maxCorner.z = glm::max(this->maxCorner.z, point.z);
}

void BoundingBox::addBox(BoundingBox *box) {
   // Min
   this->minCorner.x = glm::min(this->minCorner.x, glm::min(box->maxCorner.x, box->minCorner.x));
   this->minCorner.y = glm::min(this->minCorner.y, glm::min(box->maxCorner.y, box->minCorner.y));
   this->minCorner.z = glm::min(this->minCorner.z, glm::min(box->maxCorner.z, box->minCorner.z));
   // Max
   this->maxCorner.x = glm::max(this->maxCorner.x, glm::max(box->maxCorner.x, box->minCorner.x));
   this->maxCorner.y = glm::max(this->maxCorner.y, glm::max(box->maxCorner.y, box->minCorner.y));
   this->maxCorner.z = glm::max(this->maxCorner.z, glm::max(box->maxCorner.z, box->minCorner.z));
}