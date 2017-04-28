#include "Intersection.hpp"

using namespace std;

#define EPSILON 0.001f

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
      cout << "No Hit" << endl;
      return;
   }
   
   cout << "T = " << t << endl;
   cout << "Object Type: " << object->type << endl; 
}
