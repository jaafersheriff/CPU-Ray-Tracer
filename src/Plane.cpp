#include "Plane.hpp"

Plane::Plane() : GeoObject() {
   this->type = "Plane";

   this->normal = glm::vec3(0, 0, 0);
   this->distance = 0;
}

glm::vec3 Plane::findNormal(glm::vec3 point) {
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

glm::vec2 Plane::getUVCoords(glm::vec3 point) {
   glm::vec3 p = glm::vec3(point.x - std::floor(point.x), point.y - std::floor(point.y), point.z - std::floor(point.z)); 
   p /= 5.f;
   glm::vec2 ret;

   /* TODO: There must be a better way to do this */
   if (normal.x) {
      ret = glm::vec2(p.y, p.z);
   }
   else if (normal.y) {
      ret = glm::vec2(p.x, p.z);
   }
   else {
      ret = glm::vec2(p.x, p.y);
   }

   return ret;
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
