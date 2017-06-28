#include "Scene.hpp"
#include "Intersection.hpp"
#include "BRDF.hpp"

const static float EPSILON = 0.0001f;

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
      glm::vec3 icen = objects[i]->findCenter();
      unsigned int min = i;
      unsigned int j = i+1;
      for ( ; j < objects.size(); j++) {
        glm::vec3 jcen = objects[j]->findCenter();
        if (jcen[axis] < icen[axis]) {
          min = j;
        }
      }
      if (min != i) {
        GeoObject* temp = objects[i];
        objects[i] = objects[min];
        objects[min] = temp;
      }
  }
}

GeoObject* Scene::boxTraversal(BoxNode *node, const Ray &ray) {
	// Base Case
	if (node->objects.size() == 1) {
		return node->objects[0];
	}

	// Traversal	
	if (node->boundingBox.intersect(ray) > EPSILON) {
		if (node->leftChild != nullptr) {
			return boxTraversal(node->leftChild, ray);
		}
		if (node->rightChild != nullptr) {
			return boxTraversal(node->rightChild, ray);
		}
	}

	return nullptr;
}

glm::vec3 Scene::createSamplePoint(Intersection &intersection, glm::mat4 &matrix, float x, float y) {

	// Create point on hemisphere
	float radial = sqrt(x);
	float theta = 2.f*PI*y;
	glm::vec3 point = glm::vec3(radial*glm::cos(theta), radial*glm::sin(theta), sqrt(1-x));

	// Align hemisphere with intersection before returning
	return glm::vec3(matrix * glm::vec4(point, 1.f));
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

Ray Scene::createReflectionRay(const Intersection &intersection) {
	glm::vec3 reflection_dir = glm::normalize(intersection.ray.direction - 2 * glm::dot(intersection.ray.direction, intersection.normal) * intersection.normal);
	
	return Ray(intersection.point + reflection_dir * EPSILON, reflection_dir);
}

Ray Scene::createRefractionRay(const Intersection &intersection) {
	float n1 = 1;
	float n2 = intersection.object->finish.ior;
	glm::vec3 norm = intersection.normal;

	// If we're 'exiting' an object
	if (dot(norm, intersection.ray.direction) > 0) {
		n1 = n2;
		n2 = 1;
		norm = -norm;
	}

	float dDotN = dot(intersection.ray.direction, norm);
	float ratio = n1/n2;
	float root = 1-(ratio*ratio)*(1-dDotN*dDotN);

	glm::vec3 refraction_dir = glm::normalize(ratio*(intersection.ray.direction-dDotN*norm)-norm*(float)sqrt(root));
	
	return Ray(intersection.point + refraction_dir * EPSILON, refraction_dir);
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
