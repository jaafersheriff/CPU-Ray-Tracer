#include "Scene.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;
using namespace glm;

Intersection Scene::findIntersection(Ray ray) {
	Intersection intersection;
	intersection.ray = ray;
	intersection.t = INFINITY;
	for (int i = 0; i < objects.size(); i++) {
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

	ray.position = camera->location;

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

			/* Calculate color */
			Intersection in = findIntersection(createRay(width, height, x, y));
			if (in.hit()) {
				red = (unsigned char) 255*clamp(in.object->color.x, 0.0f, 1.0f);
				green = (unsigned char) 255*clamp(in.object->color.y, 0.0f, 1.0f);
				blue = (unsigned char) 255*clamp(in.object->color.z, 0.0f, 1.0f);
			}

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
