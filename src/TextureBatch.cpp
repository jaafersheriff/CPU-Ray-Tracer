#include "TextureBatch.hpp"
#include <iostream>  // cout

Texture* TextureBatch::addTexture(std::string name, Texture::Type type) {
   Texture *texture = new Texture(name, type);
   if (!texture->data) {
      std::cout << "Failed to create: " << name << std::endl;
      return nullptr;
   }

   textures.push_back(texture);
   
   std::cout << "Created texture: ";
   texture->print();

   return texture;
}

Texture* TextureBatch::getTexture(std::string name, Texture::Type type) {
   for (Texture *t : textures) {
      if (!name.compare(t->name) && t->type == type) {
         return t;
      }
   }

   return addTexture(name, type);
}

void TextureBatch::print() {
   std::cout << "Textures: " << textures.size() << std::endl;
   for (Texture *t : textures) {
      std::cout << t->name << std::endl;
   }
}

