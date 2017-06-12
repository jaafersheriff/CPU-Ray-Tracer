#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

Texture::Texture() {
	name = "";
   width = height = 0;
}

Texture::Texture(std::string name) {
	this->name = name;
	init();
}

void Texture::init() {
	if (strcmp(name.c_str() + name.size() - 3, "bmp") ) {
		std::cerr << "NOT A BMP FILE" << std::endl;
		return;
	}

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(name.c_str(), &width, &height, &components, 0);
	// valid data, valid componeents, image size is power of 2
	if (!data) {
		std::cerr << name << " not found" << std::endl;
		return;
	}
	if (components != 3) {
		std::cerr << name << " is not RGB" << std::endl;
		return;
	}
	if ((width & (width-1)) != 0 || (height & (height-1)) != 0) {
		std::cerr << name << " must be a power of 2" << std::endl;
		return;
	}
}

glm::vec3 Texture::getColor(glm::vec2 uv_point) {
	// UV->ST
	glm::vec2 st_point = glm::vec2(std::floor(uv_point.x * width), std::floor(uv_point.y * height));
	int index = st_point.y * (width) * components + st_point.x * components;

	if (index > width*height*components) {
		std::cerr << st_point.x << ", " << st_point.y << std::endl;
	}

	return glm::vec3(data[index], data[index+1], data[index+2]);
}

void Texture::print() {
	std::cout << name << ": " << width << "x" << height << "x" << components << std::endl;
}
