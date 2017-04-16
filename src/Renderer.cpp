#include "Renderer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" 

using namespace glm;

void Renderer::render(Scene &scene, const int window_width, const int window_height) {
	const int numChannels = 3;
	const std::string fileName = "output.png";
	const ivec2 size = ivec2(window_width, window_height);

	unsigned char *data = new unsigned char[size.x * size.y * numChannels];
	
	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			unsigned char red   = 0;
			unsigned char green = 0;
			unsigned char blue  = 0;

			// Calculate color
			// Create a ray from camera to pixel
			Ray ray = scene.createRay(size.x, size.y, x, y);
			// Create an intersection using the ray and scene
			Intersection *in = new Intersection;
		 	scene.findIntersection(*in, ray);

			// If the ray intersects an object, find the color at the intersection point
			if (in->hit()) {
				red   = (unsigned char) round(in->object->color.r * 255.f);
				green = (unsigned char) round(in->object->color.g * 255.f);
				blue  = (unsigned char) round(in->object->color.b * 255.f);
			}

			int pixel = (size.x * numChannels) * (size.y - 1 - y) + numChannels * x;
			data[pixel + 0] = red;
			data[pixel + 1] = green;
			data[pixel + 2] = blue;
		}
	}
	stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels); 
	delete[] data;
}
