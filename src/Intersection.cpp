#include "Intersection.hpp"

const static float EPSILON = 0.0001f;

Intersection::Intersection(std::vector<GeoObject *> objects, Ray& ray) {
   this->ray = ray;
   this->t = std::numeric_limits<float>::max();
   this->hit = false;

   // Loop through all objects in scene
   for (unsigned int i = 0; i < objects.size(); i++) {
      // If intersection with current object is closer to camera than current intersection
      // Replace intersection
      float curr_t = objects[i]->intersect(ray);
      if (curr_t > EPSILON && curr_t < this->t) {
         this->t = curr_t;
         this->object = objects[i];
         this->id = i+1;
      }
   }

   // If an object was hit
   if (this->t != std::numeric_limits<float>::max()) {
      this->hit = true;
      this->point = ray.calculatePoint(this->t);
   }
}

void Intersection::print() {
   if (!hit) {
      std::cout << "No Hit" << std::endl;
      return;
   }

   std::cout << "T = " << t << std::endl;
   std::cout << "Object Type: " << object->type << std::endl;
}
