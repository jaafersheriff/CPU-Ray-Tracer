#include "Scene.hpp"
#include "Intersection.hpp"
#include "BRDF.hpp"


Scene::Scene() {
   this->rootBox = new BoxNode;
}

void Scene::createNodeBoundingBox(BoxNode* parent) {
   // Leaf node
   if (parent->objects.size() <= 1) {
      parent->boundingBox.addBox(parent->objects[0]->createBox());
   }
   // Inner node
   else {
      if (parent->leftChild != nullptr) {
        parent->boundingBox.addBox(&parent->leftChild->boundingBox);
      }
      if (parent->rightChild != nullptr) {
        parent->boundingBox.addBox(&parent->rightChild->boundingBox);
      }
   }
 }

void Scene::createSpatialStructures(std::vector<GeoObject *> objects, BoxNode *parent, int axis) {
   if (objects.size() > 1) {
      sortObjects(parent->objects, axis);

      // Create left subtree
      std::vector<GeoObject *> leftObjects(objects.begin(), objects.begin() + objects.size() / 2);
      parent->leftChild = new BoxNode;
      createSpatialStructures(leftObjects, parent->leftChild, (axis+1)%3);

      // Create right subtree
      std::vector<GeoObject *> rightObjects(objects.begin() + objects.size() / 2, objects.end());
      parent->rightChild = new BoxNode;
      createSpatialStructures(rightObjects, parent->rightChild, (axis+1)%3);
   }

   parent->objects = objects;
   createNodeBoundingBox(parent);
}

void Scene::sortObjects(std::vector<GeoObject *> objects, int axis) {
   // Selection sort
   for (unsigned int i = 0; i < objects.size(); i++) {
      BoundingBox* iBox = objects[i]->createBox();
      unsigned int min = i;
      unsigned int j = i+1;
      for ( ; j < objects.size(); j++) {
         BoundingBox* jBox = objects[j]->createBox();
         if (jBox->center[axis] < iBox->center[axis]) {
            min = j;
         }
         delete jBox;
      }
      delete iBox;
      if (min != j) {
         GeoObject *temp = objects[i];
         objects[i] = objects[min];
         objects[min] = temp;
      }
   }

}

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
