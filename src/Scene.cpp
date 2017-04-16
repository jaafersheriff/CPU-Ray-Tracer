#include "Scene.h"

using namespace std;
using namespace glm;

/* This function will eventually be huge */
vec3 Scene::findColor(Intersection &in) {
	return in.object[0].color;
} 

void Scene::findIntersection(Intersection &in, const Ray &ray) {
	// Create empty intersection object
	in.ray = ray;
	in.t = INFINITY;
	// Loop through all objects
	for (int i = 0; i < objects.size(); i++) {
		// If intersection with current object is closer to camera than current intersection
		// Replace intersection
		float curr_t = objects[i]->intersect(ray);
		if (curr_t < in.t && curr_t >= 0) {
			in.t = curr_t;
			in.object = objects[i];
		}
	}
}

Ray Scene::createRay(const int width, const int height, const int x, const int y) {
	Ray ray;

	// p0
	ray.position = camera->location;

	// direction
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
