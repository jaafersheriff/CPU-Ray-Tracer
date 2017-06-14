// Texture batch class
// Holds on to all loaded textures
// Allows multiple objects to use the same texture without having 
// to load a new texture per objects

#pragma once
#ifndef _TEXTURE_BATCH_H_
#define _TEXTURE_BATCH_H_

#include <vector> 

#include "Texture.hpp"

class TextureBatch {
public:
   // List of Textures
   std::vector<Texture *> textures;


   // Get a texture from the hashmap
   Texture* getTexture(std::string, Texture::Type);

   void print();
private:
   // Add a new texture to the hashmap
   Texture* addTexture(std::string, Texture::Type);
};

#endif
