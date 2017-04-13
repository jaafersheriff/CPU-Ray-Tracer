#include "Scene.h"

using namespace std;
using namespace glm;

Intersection Scene::findIntersection(Ray ray) {
	Intersection intersection;
	intersection.ray = ray;
	intersection.t = INFINITY;
	for (int i = 0; i < objects.size(); i++) {
		float curr_t = objects[i]->intersect(ray);
		if (curr_t < intersection.t) {
			intersection.t = curr_t;
			intersection.object = objects[i];
		}
	}
	return intersection;
}

Ray Scene::createRay(const int width, const int height, const int x, const int y) {
	Ray ray;

	ray.position = camera->location;

	float u = (x + 0.5)/width - 0.5;
	float v = (y + 0.5)/height - 0.5;
	vec3 w = normalize(vec3(camera->lookAt - camera->location));
	ray.direction = normalize(vec3(u*camera->right + v*camera->up + w));

	return ray;
}

void Scene::print() {
	// Print camera
	camera->print();

	cout << endl << "---" << endl;

	// Lights
	cout << endl << lights.size() << " light(s)" << endl;  
	for(int i = 0; i < lights.size(); i++) {
		cout << endl << "Light[" << i << "]:" << endl;
		lights[i]->print();
	}

	cout << endl << "---" << endl;

	// Print objects
	cout << endl << objects.size() << " object(s)" << endl;
	for(int i = 0; i < objects.size(); i++) {
		cout << endl << "Object[" << i << "]:" << endl;
		objects[i]->print();
	}                            
}
