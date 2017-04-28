#include "Renderer.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" 

using namespace glm;

vec3 Renderer::calculateColor(Scene &scene, const ivec2 size, const int x, const int y, int BRDF_flag) {
	// Calculate color
	vec3 color = scene.findColor(size, x, y, BRDF_flag);


	return color;
}

void Renderer::render(Scene &scene, const int window_width, const int window_height) {
	const int numChannels = 3;
	const std::string fileName = "output.png";
	const ivec2 size = ivec2(window_width, window_height);

	unsigned char *data = new unsigned char[size.x * size.y * numChannels];
	
	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {

			// Calculate color
			vec3 color = calculateColor(scene, size, x, y, BRDF_flag);
	// Scale RGB
	color.r = round(color.r * 255.f);
	color.g = round(color.g * 255.f);
	color.b = round(color.b * 255.f);

			// Set pixel color
			unsigned char red   = (unsigned char) color.r;
			unsigned char green = (unsigned char) color.g;
			unsigned char blue  = (unsigned char) color.g;
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
	if (BRDF_flag)
		std::cout << "Cook-Torranec";
	else
		std::cout << "Blinn-Phong";
	std::cout << std::endl;
}