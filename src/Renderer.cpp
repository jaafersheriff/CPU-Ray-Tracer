#include "Renderer.hpp"

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

			// Calculate color
			vec3 color = scene.findColor(size, x, y, BRDF_flag);

			// Set pixel color
			unsigned char red   = (unsigned char) round(color.r * 255.f);
			unsigned char green = (unsigned char) round(color.g * 255.f);
			unsigned char blue  = (unsigned char) round(color.b * 255.f);
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
