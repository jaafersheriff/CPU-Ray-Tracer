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
	return getPixelColor(st_point);

	// TODO: Bilinear interpolation -- make this a flag option?
	// glm::vec2 uvp = glm::vec2(uv_point.x * width - st_point.x, uv_point.y * height - st_point.y);
	// return (1-uvp.x)*(1-uvp.y)*getPixelColor(st_point) + uvp.x*(1-uvp.y)*getPixelColor(glm::vec2(st_point.x+1, st_point.y)) + (1-uvp.x)*uvp.y*getPixelColor(glm::vec2(st_point.x, st_point.y+1)) + uvp.x*uvp.y*getPixelColor(glm::vec2(st_point.x+1, st_point.y+1));
}

glm::vec3 Texture::getPixelColor(glm::vec2 st_point) {
	int index = st_point.y * (width) * components + st_point.x * components;
	return glm::vec3(data[index], data[index+1], data[index+2]);
}

void Texture::print() {
	std::cout << name << ": " << width << "x" << height << "x" << components << std::endl;
}
