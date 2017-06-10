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

	data = stbi_load(name.c_str(), &width, &height, &components, 0);
	// valid data, valid componeents, image size is power of 2
	if (!data || components != 3 || (width & (width-1)) != 0 || (height & (height-1)) != 0) {
		std::cerr << "ERROR OPENING TEXTURE: " << name << std::endl;
		return;
	}

	std::cout << name << " created: " << width << "x" << height << "x" << components << std::endl;
}

glm::vec3 Texture::getColor(glm::vec2 point) {
	int index = point.y * point.x + point.x;
	return glm::vec3(data[index], data[index+1], data[index+2]);
}
