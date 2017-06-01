#include "Plane.hpp"

Plane::Plane() : GeoObject() {
   this->type = "Plane";

   this->normal = glm::vec3(0, 0, 0);
   this->distance = 0;
}

glm::vec3 Plane::findNormal(Ray &ray, float t) {
   return normal;
}

glm::vec3 Plane::findCenter() {
   // No such center for plane
   return glm::vec3(0, 0, 0);
}

float Plane::intersect(const Ray &ray) {
   float den = dot(ray.direction, normal);
   if (!den) {
      return -1;
   }
   float num = distance-dot(ray.position, normal);
   return num/den;
}

BoundingBox* Plane::createBox() {
   // Planes will never need a bounding box
   return new BoundingBox;
}

void Plane::print() {
   std::cout << "- Type: Plane" << std::endl;
   std::cout << "- Normal: {";
      std::cout << normal.x << " " << normal.y << " " << normal.z;
      std::cout << "}" << std::endl;
   std::cout << "- Distance: ";
      std::cout << distance << std::endl;
   GeoPrint();
}
