#include "BoxRenderable.hpp"
#include "glm/gtc/epsilon.hpp"   // Epsilon equals

BoxRenderable::BoxRenderable() : GeoObject(), Box() {
   this->type = "Box";
}

void BoxRenderable::updateBox(glm::vec3 min, glm::vec3 max) {
   Box::updateBox(min, max);
}

BoundingBox* BoxRenderable::createBox() {
   BoundingBox *box = new BoundingBox(this->minCorner, this->maxCorner);
   box->transform(this->inv_M);
   return box;
}

float BoxRenderable::intersect(const Ray &ray) {
   return Box::intersect(ray);
}

glm::vec3 BoxRenderable::findCenter() {
   return this->center;
}

static inline bool Equals(const float a, const float b, const float epsilon = 0.0001f) {
   return std::abs(a - b) < epsilon;
}

glm::vec3 BoxRenderable::findNormal(Ray &ray, const float t) {
   // Check for uninitialized box
   if (!this->hasBeenInit()) {
      return glm::vec3(0, 0, 0);
   }
   glm::vec3 intersection_point = ray.calculatePoint(t);
   
   glm::vec3 normal = glm::vec3(0, 0, 0);
   // X
   if (Equals(intersection_point.x, this->minCorner.x)) {
      normal = glm::vec3(-1, 0, 0);
   }
   else if (Equals(intersection_point.x, this->maxCorner.x)) {
      normal = glm::vec3(1, 0, 0);
   }
   // Y
   else if (Equals(intersection_point.y, this->minCorner.y)) {
      normal = glm::vec3(0, -1, 0);
   }
   else if (Equals(intersection_point.y, this->maxCorner.y)) {
      normal = glm::vec3(0, 1, 0);
   }
   // Z
   else if (Equals(intersection_point.z, this->minCorner.z)) {
      normal = glm::vec3(0, 0, -1);
   }
   else if (Equals(intersection_point.z, this->maxCorner.z)) {
      normal = glm::vec3(0, 0, 1);
   }

   return normal;
}

void BoxRenderable::print() {
   std::cout << "THIS IS A BOX" << std::endl;
}