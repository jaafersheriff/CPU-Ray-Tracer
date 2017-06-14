// Texture class
// Holds all data regarding textures

#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>
#include <glm/glm.hpp>

class Texture {
public:
   enum Type {
      ColorMap,
      NormalMap,
      BumpMap
   };


   // Take in a file name and create a new texture
   Texture();
   Texture(std::string, Type);

   std::string name;
   Type type;
	int width;
	int height;
	int components;
	unsigned char *data;
    
	void init();  
   glm::vec3 getColor(glm::vec2);
	void print();

private:
	glm::vec3 getPixelColor(glm::vec2);
};

#endif
