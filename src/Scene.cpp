#include "Scene.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;
using namespace glm;

Intersection Scene::findIntersection(Ray ray) {
	// Create empty intersection object
	Intersection intersection;
	intersection.ray = ray;
	intersection.t = INFINITY;
	// Loop through all objects
	for (int i = 0; i < objects.size(); i++) {
		// If intersection with current object is closer to camera than current intersection
		// Replace intersection
		float curr_t = objects[i]->intersect(ray);
		if (curr_t < intersection.t && curr_t >= 0) {
			intersection.t = curr_t;
			intersection.object = objects[i];
		}
	}
	return intersection;
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

void Scene::render(const int width, const int height) {
	const int numChannels = 3;
	const string fileName = "output.png";
	const ivec2 size = ivec2(width, height);

	unsigned char *data = new unsigned char[size.x * size.y * numChannels];

	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			unsigned char red = 0;
			unsigned char green = 0;
			unsigned char blue  = 0;

			/*=== Calculate color ===*/
			// Create a ray from camera to pixel
			// Create an Intersection object using that ray
			Intersection in = findIntersection(createRay(width, height, x, y));
			
			// If the ray intersected an object, color the pixel using the object's RGB values
			if (in.hit()) {
				red   = (unsigned char) round(in.object->color.r * 255.f);
				green = (unsigned char) round(in.object->color.g * 255.f);
				blue  = (unsigned char) round(in.object->color.b * 255.f);
			}
			/*=======================*/

			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 0] = red;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 1] = green;
			data[(size.x * numChannels) * (size.y - 1 - y) + numChannels * x + 2] = blue;
		}
	}
	
	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	delete[] data;
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
