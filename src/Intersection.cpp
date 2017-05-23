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
		// Transform ray into object's object space

		glm::vec3 p = glm::vec3(glm::vec4(ray.position, 1.0f) * objects[i]->inv_M);
		glm::vec3 d = glm::vec3(glm::vec4(ray.direction, 0.0f) * objects[i]->inv_M);
		Ray objectRay(p, d);

      // Store t value and object if there's a closer intersection
      float curr_t = objects[i]->intersect(objectRay);
      if (curr_t > EPSILON && curr_t < this->t) {
         this->t = curr_t;
         this->object = objects[i];
      }
   }

   // If there was a valid intersection, store point of intersection and object's normal
   if (this->t != std::numeric_limits<float>::max()) {
      this->hit = true;
      this->point = this->ray.calculatePoint(this->t);
		// Coordinate transform normal
		this->normal = glm::vec3(glm::vec4(this->object->findNormal(this->point), 0.0f) * glm::transpose(this->object->inv_M));
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
