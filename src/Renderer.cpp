#include "Renderer.hpp"
#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

glm::vec3 Renderer::calculateColor(Scene &scene, const glm::ivec2 size, const int x, const int y) {

	// Calculate color
	Ray camera_ray = scene.createCameraRay(size.x, size.y, x, y);
	glm::vec3 color = brdf.raytrace(scene.objects, scene.lights, camera_ray, RECURSE_COUNT);

	// Scale RGB
	color.r = round(glm::clamp(color.r, 0.f, 1.f) * 255.f);
	color.g = round(glm::clamp(color.g, 0.f, 1.f) * 255.f);
	color.b = round(glm::clamp(color.b, 0.f, 1.f) * 255.f);

	return color;
}

void Renderer::render(Scene &scene, const int window_width, const int window_height) {
	const int numChannels = 3;
	const std::string fileName = "output.png";
	const glm::ivec2 size = glm::ivec2(window_width, window_height);

	unsigned char *data = new unsigned char[size.x * size.y * numChannels];

	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {

			// Calculate color
			glm::vec3 color = calculateColor(scene, size, x, y);

			// Set pixel color
			unsigned char red   = (unsigned char) color.r;
			unsigned char green = (unsigned char) color.g;
			unsigned char blue  = (unsigned char) color.b;
			int pixel = (size.x * numChannels) * (size.y - 1 - y) + numChannels * x;
			data[pixel + 0] = red;
			data[pixel + 1] = green;
			data[pixel + 2] = blue;
		}
	}
	int success = stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels);
	if (!success) {
		std::cout << "FAILED WRITING IMAGE" << std::endl;
	}
	delete[] data;
}

void Renderer::print() {
	std::cout << "BRDF: ";
	if (brdf.render_flag)
		std::cout << "Cook-Torranec";
	else
		std::cout << "Blinn-Phong";
	std::cout << std::endl;
}
