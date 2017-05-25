#include "Scene.hpp"
#include "Intersection.hpp"
#include "BRDF.hpp"

Ray Scene::createCameraRay(const int width, const int height, const int x, const int y, const int m, const int n, const int s) {
   Ray ray;

   // p0
   ray.position = camera->location;

   // direction
   float u = (x + (m + 0.5) / s)/width - 0.5;
   float v = (y + (n + 0.5) / s)/height - 0.5;
   glm::vec3 w = glm::normalize(glm::vec3(camera->lookAt - camera->location));
   ray.direction = glm::normalize(glm::vec3(u*camera->right + v*camera->up + w));

   return ray;
}

void Scene::print() {
   // Print camera
   camera->print();
   std::cout << std::endl << "---" << std::endl;

   // Lights
   std::cout << std::endl << lights.size() << " light(s)" << std::endl;
   for(unsigned int i = 0; i < lights.size(); i++) {
      std::cout << std::endl << "Light[" << i << "]:" << std::endl;
      lights[i]->print();
   }
   std::cout << std::endl << "---" << std::endl;

   // Print objects
   std::cout << std::endl << objects.size() << " object(s)" << std::endl;
   for(unsigned int i = 0; i < objects.size(); i++) {
      std::cout << std::endl << "Object[" << i << "]:" << std::endl;
      objects[i]->print();
   }
}
