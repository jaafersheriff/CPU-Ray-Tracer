#include "BoxRenderable.hpp"


BoxRenderable::BoxRenderable() : GeoObject(), Box() {

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

glm::vec3 BoxRenderable::findNormal(Ray &ray, const float t) {
   glm::vec3 intersection_point = ray.calculatePoint(t); 
   updateBox(this->minCorner, this->maxCorner);

   glm::vec3 normal = glm::vec3(0, 0, 0);
   glm::vec3 local_point = intersection_point - center;  // Center works?
   
   float min = std::numeric_limits<float>::max();
   float dist = std::abs(std::abs(maxCorner.x - minCorner.x) - std::abs(local_point.x));
   if (dist < min) {
      min = dist;
      normal = glm::vec3(1, 0, 0);
      if (local_point.x < 0) {
         normal = -normal;
      }
   }
   dist = std::abs(std::abs(maxCorner.y - minCorner.y) - std::abs(local_point.y));
   if (dist < min) {
      min = dist;
      normal = glm::vec3(0, 1, 0);
      if (local_point.y < 0) {
         normal = -normal;
      }
   }
   dist = std::abs(std::abs(maxCorner.z - minCorner.z) - std::abs(local_point.z));
   if (dist < min) {
      min = dist;
      normal = glm::vec3(0, 0, 1);
      if (local_point.z < 0) {
         normal = -normal;
      }
   }
   return glm::normalize(normal);

}

void BoxRenderable::print() {
   std::cout << "THIS IS A BOX" << std::endl;
}