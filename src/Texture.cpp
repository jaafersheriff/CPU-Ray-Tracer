#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

Texture::Texture() {
	name = "";
   width = height = 0;
}

Texture::Texture(std::string name, Type type) {
	this->name = name;
   this->type = type;
	init();
}

void Texture::init() {
	if (strcmp(name.c_str() + name.size() - 3, "bmp") ) {
		std::cerr << name << " is not a .bmp file"  << std::endl;
		return;
	}

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(name.c_str(), &width, &height, &components, 0);


   // Ensure valid data
   int errorFlag = 0;
	if (!data) {
		std::cerr << name << " not found" << std::endl;
      errorFlag = 1;
	}
	if (components != 3) {
		std::cerr << name << " is not RGB" << std::endl;
      errorFlag = 1;
	}
	if ((width & (width-1)) != 0 || (height & (height-1)) != 0) {
		std::cerr << name << " must be a power of 2" << std::endl;
      errorFlag = 1;
	}

   if (errorFlag) {
      width = height = components = 0;
      data = nullptr;
  }
}

glm::vec3 Texture::getColor(glm::vec2 uv_point) {
	// UV->ST
	glm::vec2 st_point = glm::vec2(std::floor(uv_point.x * width), std::floor(uv_point.y * height));

	// Bilinear interpolation 
	glm::vec2 uvp = glm::vec2(uv_point.x * width - st_point.x, uv_point.y * height - st_point.y);
	return (1-uvp.x)*(1-uvp.y)*getPixelColor(st_point) + uvp.x*(1-uvp.y)*
          getPixelColor(glm::vec2(st_point.x+1, st_point.y)) + (1-uvp.x)*
          uvp.y*getPixelColor(glm::vec2(st_point.x, st_point.y+1)) + 
          uvp.x*uvp.y*getPixelColor(glm::vec2(st_point.x+1, st_point.y+1));
}

glm::vec3 Texture::getPixelColor(glm::vec2 st_point) {
	int index = st_point.y * (width) * components + st_point.x * components;
	return glm::vec3(data[index]/255.f, data[index+1]/255.f, data[index+2]/255.f);
}

void Texture::print() {
   switch(type) {
      case ColorMap:
         std::cout << "Color Map: ";
         break;
      case NormalMap:
         std::cout << "Normal Map: ";
         break;
      case BumpMap: 
         std::cout << "Bump Map: ";
         break;
      default:
         std::cout << "No type: "; 
         break;
   }
	std::cout << name << ": " << width << "x" << height << "x" << components << std::endl;
}
