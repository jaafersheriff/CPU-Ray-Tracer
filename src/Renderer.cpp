#include "Renderer.hpp"
#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

glm::vec3 Renderer::calculateColor(Scene &scene, const glm::ivec2 size, const int x, const int y) {
	if (brdf.verbose_flag) {
		root = new BRDF::printNode;
		root->type = "Primary";
	}
	// Calculate color
	Ray camera_ray = scene.createCameraRay(size.x, size.y, x, y);
	glm::vec3 color = brdf.raytrace(scene, camera_ray, RECURSE_COUNT, root);

	// Scale RGB from [0, 1] to [0, 255]
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
	if (!stbi_write_png(fileName.c_str(), size.x, size.y, numChannels, data, size.x * numChannels)) {
		std::cout << "FAILED WRITING IMAGE" << std::endl;
	}
	delete[] data;
}

void Renderer::print() {
	std::cout << "BRDF: ";
	if (brdf.render_flag)
		std::cout << "Cook-Torrance";
	else
		std::cout << "Blinn-Phong";
	std::cout << std::endl;
}

void Renderer::printRays(BRDF::printNode* p, int level) {
	if (p == nullptr) {
		return;
	}

	if (level > 0) {
		for (int i = 1; i < level; i++) { std::cout << "  "; }
		std::cout << " \\" << std::endl;;
	}

	for (int i = 0; i < level; i++) { std::cout << "  "; }
	std::cout << "o - Iteration type: " << p->type << std::endl;

	for (int i = 0; i < level; i++) { std::cout << "  "; }
	std::cout << "|   Ray: "; p->in.ray.print();

	if (p->in.hit) {
		for (int i = 0; i < level; i++) { std::cout << "  "; }
		std::cout << "|   Hit Object ID (" << p->in.object->id << " - " << p->in.object->type << ") at T = " << p->in.t;
		std::cout << ", Intersection = {" << p->in.point.x << " " << p->in.point.y << " " << p->in.point.z << "}" << std::endl;

		for (int i = 0; i < level; i++) { std::cout << "  "; }
		std::cout << "|   Normal {" << p->norm.x << " " << p->norm.y << " " << p->norm.z << "}" << std::endl;

		for (int i = 0; i < level; i++) { std::cout << "  "; }
		std::cout << "|   Transformed Ray: "; p->in.ray.print();

		for (int i = 0; i < level; i++) { std::cout << "  "; }
		std::cout << "|   ShadowRay [0] "; p->shadow_ray.print();

		for (int i = 0; i < level; i++) { std::cout << "  "; }
		std::cout << "|   Ambient: " << p->ambient.x << ", " << p->ambient.y << ", " << p->ambient.z << std::endl;
		for (int i = 0; i < level; i++) { std::cout << "  "; }
		std::cout << "|   Diffuse: " << p->diffuse.x << ", " << p->diffuse.y << ", " << p->diffuse.z << std::endl;
		for (int i = 0; i < level; i++) { std::cout << "  "; }
		std::cout << "|   Specular: " << p->specular.x << ", " << p->specular.y << ", " << p->specular.z << std::endl;

	}
	for (int i = 0; i < level; i++) { std::cout << "  "; }
	std::cout << "|" << std::endl;

	printRays(p->refr, level+1);
	printRays(p->refl, level+1);
}
