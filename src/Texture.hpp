// Texture class
// Holds all data regarding textures

#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>
#include <glm/glm.hpp>

class Texture {
public:
   // Take in a file name and create a new texture
   Texture();
   Texture(std::string);

   std::string name;
      
   /* TODO: Any other texture-specific data */
   glm::vec3 getColor(glm::vec2);
};

#endif