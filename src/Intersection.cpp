#include "Intersection.hpp"

const static float EPSILON = 0.0001f;

Intersection::Intersection(std::vector<GeoObject *> objects, Ray& ray) {
	// Store incoming ray
   this->ray = ray;
	
	// Init hit and t values
   this->hit = false;
   this->t = std::numeric_limits<float>::max();

   // Loop through all objects in scene
   for (unsigned int i = 0; i < objects.size(); i++) {
      // Store t value and object if there's a closer intersection
      float curr_t = objects[i]->intersect(ray);
      if (curr_t > EPSILON && curr_t < this->t) {
         this->t = curr_t;
         this->object = objects[i];
      }
   }

   // If there was a valid intersection, store point of intersection and object's normal
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
