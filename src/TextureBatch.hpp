// Texture batch class
// Holds on to all loaded textures
// Allows multiple objects to use the same texture without having 
// to load a new texture per objects

#pragma once
#ifndef _TEXTURE_BATCH_H_
#define _TEXTURE_BATCH_H_

#include <map>

#include "Texture.hpp"

class TextureBatch {
public:
   // Hashmap of textures
   std::map<std::string, Texture*> textures;

   // Add a new texture to the hashmap
   Texture* addTexture(std::string);

   // Get a texture from the hashmap
   Texture* getTexture(std::string);
};

#endif