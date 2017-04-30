#include "Intersection.hpp"

#define EPSILON 0.0001f

Intersection::Intersection(Scene* scene, Ray& ray) {
   this->ray = ray;
   this->t = INFINITY;

   // Loop through all objects in scene
   for (unsigned int i = 0; i < scene->objects.size(); i++) {
      // If intersection with current object is closer to camera than current intersection
      // Replace intersection
      float curr_t = scene->objects[i]->intersect(ray);
      if (curr_t < this->t && curr_t > EPSILON) {
         this->t = curr_t;
         this->object = scene->objects[i];
      }
   }
   // Set final intersection point and return
   this->point = ray.intersection_point(this->t);
}

void Intersection::print() {
   if (!hit()) {
      std::cout << "No Hit" << std::endl;
      return;
   }
   
   std::cout << "T = " << t << std::endl;
   std::cout << "Object Type: " << object->type << std::endl; 
}
